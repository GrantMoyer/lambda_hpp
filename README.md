λ.hpp is a syntatic sugar, dubbed λ expressions, for C++20 lambdas. The syntax is reminicent of Scala's [placeholder syntax][1], but not identical.

[1]: https://scala-lang.org/files/archive/spec/3.4/06-expressions.html#placeholder-syntax-for-anonymous-functions

## Example usage

λ expressions can be used in most places a lambda can be used.

λ expressions can use _1, _2, _3, and _4 as implicitly defined positional arguments.

```c++
array arr{8, 5, 4, 2, 9, 6, 7, 3, 1};
ranges::sort(arr, λ(_1 > _2));
```
> 9, 8, 7, 6, 5, 4, 3, 2, 1

For convenience "_" may be used as an alias for "_1".

```c++
auto e = *ranges::find_if(arr, λ(_ < 4));
```

> 3

Trying to use an unexpected parameter results in a compile error.

```c++
ranges::find_if(arr, λ(_2 < 4)); // illegal
```

> ```
> error: invalid operands to binary expression ('λ::unassigned' and 'int')
>     ranges::find_if(arr, λ(_2 < 4)); // illegal
>                            ~~ ^ ~
> ```

λ expressions implicitly capture variables by reference.

```c++
auto m = 3;
auto n = ranges::count_if(arr, λ(_ % m == 0));
```

> 3

Not all available parameters need to be used in a λ expression.

```c++
ranges::transform(arr, arr.data(), λ(0));
```

> 0, 0, 0, 0, 0, 0, 0, 0, 0

Methods on λ expression parameters can be called like normal.

```c++
array<string, 9> arr2{};
char c = 'a';
ranges::for_each(arr2, λ(_.push_back(c++)));
```

> a, b, c, d, e, f, g, h, i

It's even possible to store a λ expression to an intermediate variable.

```c++
auto join_with_dash = λ(_1 + '-' + _2);
auto s = reduce(arr2.begin() + 1, arr2.end(), arr2[0], join_with_dash);
```

> a-b-c-d-e-f-g-h-i
