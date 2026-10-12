#ifndef PACK_H
#define PACK_H

namespace pack_detail {

// generic pack size
template <typename... Args>
constexpr int packSize = static_cast<int>(sizeof...(Args));

template <int QueryIndex, typename... Args>
struct _packIndexToType {
    static_assert(sizeof...(Args) > 0, "QueryIndex is out of bounds for the given pack size");
};

// base case for recursion
template <typename First, typename... Rest>
struct _packIndexToType<0, First, Rest...> {
    using type = First;
};

// recursive case for recursion
template <int QueryIndex, typename First, typename... Rest>
struct _packIndexToType<QueryIndex, First, Rest...> {
    using type = typename _packIndexToType<QueryIndex - 1, Rest...>::type;
};

// helper type alias for packIndexToType
template <int QueryIndex, typename... Args>
    requires(QueryIndex >= 0 && QueryIndex < packSize<Args...>)
using packIndexToType = typename _packIndexToType<QueryIndex, Args...>::type;

// helper variable template for packTypeToIndex
template <int Accumulated, typename QueryType, typename... Args>
constexpr int _packTypeToIndex = -1;

// recursive case for packTypeToIndex
template <int Accumulated, typename QueryType, typename First, typename... Rest>
constexpr int _packTypeToIndex<Accumulated, QueryType, First, Rest...> =
    _packTypeToIndex<Accumulated + 1, QueryType, Rest...>;

// base case for packTypeToIndex when the type is found
template <int Accumulated, typename QueryType, typename... Rest>
constexpr int _packTypeToIndex<Accumulated, QueryType, QueryType, Rest...> = Accumulated;

// helper variable template for packTypeToIndex
template <typename QueryType, typename... Args>
constexpr int packTypeToIndex = _packTypeToIndex<0, QueryType, Args...>;

}  // namespace pack_detail

// main Pack struct
template <typename... Args>
struct Pack {
    static constexpr int size = pack_detail::packSize<Args...>;

    template <int QueryIndex>
    using type = pack_detail::packIndexToType<QueryIndex, Args...>;

    template <typename QueryType>
    static constexpr int index = pack_detail::packTypeToIndex<QueryType, Args...>;
};

#endif  // PACK_H
