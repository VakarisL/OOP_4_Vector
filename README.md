# OOP_4_Vector
OOP Task 4 - An attempt to recreate/copy std::vector realization

## No Optimisation
| n | 10000 | 100000 | 1000000 | 10000000 | 100000000
| :-------------: |:-------------:| :-----:|  :-----:|  :-----: |  :-----:
| Vector      | 0.001069s | 0.001024s |  0.012584s |  0.105318s|  1.20033s
| std::vector      | 0.000997s | 0.003059s | 0.027293s|  0.262785s |  1.

## -O1
| n | 10000 | 100000 | 1000000 | 10000000 | 100000000
| :-------------: |:-------------:| :-----:|  :-----:|  :-----: |  :-----:
| Vector      | 0.002151s | 0.002841s |  0.024214s |  0.257127s|  2.3869s
| std::vector      | 0s | 0.000997s | 0.006678s|  0.065095s |  0.570939s


## -O2
| n | 10000 | 100000 | 1000000 | 10000000 | 100000000
| :-------------: |:-------------:| :-----:|  :-----:|  :-----: |  :-----:
| Vector      | 0.000997s | 0.002003s |  0.007071s |  0.075673s|  0.717879s
| std::vector      | 0s | 0.001232s | 0.006023s|  0.077474s |  0.62091s


## -O3
| n | 10000 | 100000 | 1000000 | 10000000 | 100000000
| :-------------: |:-------------:| :-----:|  :-----:|  :-----: |  :-----:
| Vector      | 0s | 0s |  0.078145s |  0.437387s|  2.28198s
| std::vector      | 0s | 0s | 0s|  0.062508s |  0.484262s


## Mildly Interesting Stuff
```C++
template<class T, class Allocator>
Vector<T, Allocator>::Vector(std::size_t size, const T& value /*, Allocator alloc*/)
  : capacity_(size), size_(size), element_{allocator_.allocate(capacity_)} {
  std::fill_n(element_, size, value);
}
```