/*
inversify-cpp dependency visualization tool
Version 1.0.0
https://github.com/mosure/inversify-cpp-visualizer

MIT License

Copyright (c) 2020 Mitchell Mosure

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <map>
#include <ostream>
#include <set>
#include <stdexcept>
#include <string>
#include <tuple>
#include <typeinfo>

#include <boost/core/demangle.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

#include <mosure/inversify.hpp>

#ifndef INVERSIFY_BINDING_INSPECTION
#error Define INVERSIFY_BINDING_INSPECTION before including inversify.hpp
#endif


/**
    @brief namespace for Mitchell Mosure - inversify-cpp-visualizer
    @see https://github.com/mosure
    @since version 1.0.0
*/
namespace mosure::inversify_visualizer {

namespace {

struct VertexProps { std::string name; };

using Graph = boost::adjacency_list<
    boost::vecS,
    boost::vecS,
    boost::directedS,
    VertexProps
>;

using StdGraph = std::map<std::size_t, std::set<std::size_t>>;

template <typename T>
std::string get_type_name() {
    return boost::core::demangle(typeid(T).name());
}

template <typename T>
int get_type_id() {
    return typeid(T).hash_code();
}

template <typename... SymbolTypes>
std::string get_label(inversify::Container<SymbolTypes...>& container, std::size_t id) {
    std::tuple<SymbolTypes...> symbols;

    std::string result;

    auto unroll = [&container, id, &result](auto... symbols) {
        auto id_to_label = [&container, id, &result](auto symbol) {
            using Symbol = decltype(symbol);

            if (id != get_type_id<Symbol>()) {
                return;
            }

            auto resolver = container.template bind<Symbol>().getResolver();

            auto impl_label = boost::core::demangle(resolver->getImplementationLabel().c_str());
            auto intf_label = get_type_name<typename Symbol::value>();
            auto is_dup_label = impl_label == intf_label;

            result = resolver->getResolverLabel() + "\\n" + intf_label;

            if (!is_dup_label) {
                result += "\n" + impl_label;
            }
        };
        (id_to_label(symbols), ...);
    };
    std::apply(unroll, symbols);

    return result;
}

template <typename... SymbolTypes>
Graph to_boost_graph(inversify::Container<SymbolTypes...>& container, StdGraph std_graph) {
    Graph g {std_graph.size()};

    std::map<std::size_t, int> node_remap;
    for (const auto& pair : std_graph) {
        node_remap[pair.first] = node_remap.size();
    }

    for (const auto& pair : std_graph) {
        g[node_remap[pair.first]].name = get_label(container, pair.first);

        for (const auto& dep : pair.second) {
            boost::add_edge(node_remap[dep], node_remap[pair.first], g);
        }
    }

    return g;
}
}

template <typename Symbol, typename... SymbolTypes>
void fill_graph(inversify::Container<SymbolTypes...>& container, StdGraph& result) {
    auto current_symbol = get_type_id<Symbol>();

    if (result.find(current_symbol) == result.end()) {
        auto resolver = container.template bind<Symbol>().getResolver();
        auto dep_tuple = resolver->getDependencies().values;

        auto& nodes = result[current_symbol];
        auto unroll = [&container, &nodes, &result](auto... deps) {
            auto add_node = [&container, &nodes, &result](auto dep) {
                if (!dep) {
                    return;
                }

                using Dependency = typename decltype(dep)::symbol;

                auto dep_symbol = get_type_id<Dependency>();
                nodes.insert(dep_symbol);

                fill_graph<Dependency>(container, result);
            };
            (add_node(deps), ...);
        };
        std::apply(unroll, dep_tuple);
    }
}

template <typename... SymbolTypes>
void write_graphviz(
    std::ostream& out,
    inversify::Container<SymbolTypes...>& container
) {
    std::tuple<SymbolTypes...> symbols;

    StdGraph result;
    auto unroll = [&container, &result](auto... symbols) {
        auto do_fill = [&container, &result](auto symbol) {
            using Symbol = decltype(symbol);

            fill_graph<Symbol>(container, result);
        };
        (do_fill(symbols), ...);
    };
    std::apply(unroll, symbols);

    auto graph = to_boost_graph(container, result);
    boost::write_graphviz(
        out,
        graph,
        boost::make_label_writer(boost::get(&VertexProps::name, graph))
    );
}
}
