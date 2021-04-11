#include <iostream>

#include <mosure/inversify.hpp>
#include <mosure/visualizer.hpp>


namespace inversify = mosure::inversify;
namespace inversify_visualizer = mosure::inversify_visualizer;


struct A;
struct B;
struct C;
struct D;
struct E;
struct F;

namespace symbols {
    using foo = inversify::Symbol<int>;
    using bar = inversify::Symbol<double>;
    using A = inversify::Symbol<A>;
    using B = inversify::Symbol<B>;
    using C = inversify::Symbol<C>;
    using D = inversify::Symbol<D>;
    using E = inversify::Symbol<E>;
    using F = inversify::Symbol<F>;
}

struct A { };

struct B { B(A, int){} };
template <>
struct inversify::Injectable<B>
    : inversify::Inject<
        symbols::A,
        symbols::foo
    >
{ };

struct C { C(B){} };
template <>
struct inversify::Injectable<C>
    : inversify::Inject<
        symbols::B
    >
{ };

struct D { D(B, int, double){} };
template <>
struct inversify::Injectable<D>
    : inversify::Inject<
        symbols::B,
        symbols::foo,
        symbols::bar
    >
{ };

struct E { E(D, double){} };
template <>
struct inversify::Injectable<E>
    : inversify::Inject<
        symbols::D,
        symbols::bar
    >
{ };

struct F { };


int main() {
    inversify::Container<
        symbols::foo,
        symbols::bar,
        symbols::A,
        symbols::B,
        symbols::C,
        symbols::D,
        symbols::E,
        symbols::F
    > container;

    container.bind<symbols::foo>().toConstantValue(5);
    container.bind<symbols::bar>().toDynamicValue([](auto& ctx) {
        auto foo = ctx.container.template get<symbols::foo>();

        return foo * 1.5;
    });

    container.bind<symbols::A>().to<A>().inSingletonScope();
    container.bind<symbols::B>().to<B>();
    container.bind<symbols::C>().to<C>();
    container.bind<symbols::D>().to<D>();
    container.bind<symbols::E>().to<E>();
    container.bind<symbols::F>().to<F>();

    inversify_visualizer::write_graphviz(std::cout, container);

    return 0;
}
