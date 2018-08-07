# Algorithms and Data Structures in ReasonML
Implementation of data structures and algorithms introduced in MIT OCW [6006](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/index.htm) and [6046](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-046j-design-and-analysis-of-algorithms-spring-2015/) in [ReasonML](https://reasonml.github.io/).

*Currently focusing on data structures and algorithms introduced in 6006*

## Interested in Contributing?
Checkout the [contribution guidelines](https://github.com/Artris/algorithms/blob/master/CONTRIBUTING.md).

## 6006 Algorithms and Data Structures

| Alg / DS | Lecture | Implementation |
|---|---|---|
| Insertion Sort | [Lec 3](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-3-insertion-sort-merge-sort/) | [sort / InsertionSort.re](https://github.com/Artris/algorithms/blob/master/src/sort/InsertionSort.re) |
| Merge Sort | [Lec 3](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-3-insertion-sort-merge-sort/) | [sort / MergeSort.re](https://github.com/Artris/algorithms/blob/master/src/sort/MergeSort.re) |
| Heaps | [Lec 4](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-4-heaps-and-heap-sort/) | [basic / Heap.re](https://github.com/Artris/algorithms/blob/master/src/basic/Heap.re) |
| AVL Trees | [Lec 6](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-6-avl-trees-avl-sort/) | |
| Counting Sort | [Lec 7](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-7-counting-sort-radix-sort-lower-bounds-for-sorting/) | [sort / integer_sort / CountingSort.re](https://github.com/Artris/algorithms/blob/master/src/sort/integer_sort/CountingSort.re) |
| Radix Sort | [Lec 7](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-7-counting-sort-radix-sort-lower-bounds-for-sorting/) | [sort / integer_sort / RadixSort.re](https://github.com/Artris/algorithms/blob/master/src/sort/integer_sort/RadixSort.re) |
| Hashing with Chaining | [Lec 8](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-8-hashing-with-chaining/) | [hashing / HashtblWithChaining.re](https://github.com/Artris/algorithms/blob/master/src/hashing/HashtblWithChaining.re) |
| Table Doubling | [Lec 9](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-9-table-doubling-karp-rabin/) | [basic / DynamicArray.re](https://github.com/Artris/algorithms/blob/master/src/basic/DynamicArray.re) |
| Rolling Hash | [Lec 9](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-9-table-doubling-karp-rabin/) | [hashing / RollingHash.re](https://github.com/Artris/algorithms/blob/master/src/hashing/RollingHash.re) |
| Karp-Rabin | [Lec 9](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-9-table-doubling-karp-rabin/) | [hashing / KarpRabin.re](https://github.com/Artris/algorithms/blob/master/src/hashing/KarpRabin.re) |
| Hashing with Open Addressing | [Lec 10](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-10-open-addressing-cryptographic-hashing/) | [hashing / HashtblWithOpenAddressing.re](https://github.com/Artris/algorithms/blob/master/src/hashing/HashtblWithOpenAddressing.re) |
| Karatsuba Multiplication | [Lec 11](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-11-integer-arithmetic-karatsuba-multiplication/) | |
| Breadth-First Search (BFS) | [Lec 13](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-13-breadth-first-search-bfs/) | [graphs / BreadthFirstSearch.re](https://github.com/Artris/algorithms/blob/master/src/graphs/BreadthFirstSearch.re) |
| Depth-First Search (DFS) | [Lec 14](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-14-depth-first-search-dfs-topological-sort/) | |
| Topological Sort | [Lec 14](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-14-depth-first-search-dfs-topological-sort/) | |
| Dijkstra | [Lec 16](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-16-dijkstra/) | |
| Bellman-Ford | [Lec 17](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/lecture-17-bellman-ford/) | |