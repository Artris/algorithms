# Contributing
- If you discover an issue with a current implementation please open an issue.
- If you want to optimize or refactor an existing Alg./DS, please open an issue first.
- If you want to implement an Alg./DS please comment in the [distribution of work issue](https://github.com/Artris/algorithms/issues/3). This is to make sure only one person is working on a feature at a time.

## Making a Pull Request
Please read [How to GitHub: Fork, Branch, Track, Squash and Pull Request](https://www.gun.io/blog/how-to-github-fork-branch-and-pull-request)

- Create a branch with the same name as the Alg./DS you're working on
- Implement your solution in a [module](http://2ality.com/2017/12/modules-reasonml.html) and make sure to provide a [signature](https://reasonml.github.io/docs/en/module#signatures) for your module
- Add unit tests for all the functions specified in the signature file. We are using [bs-jest](https://github.com/glennsl/bs-jest) for unit tests
- When you're happy with your solution create a pull request against the `master` branch
- Address the comments on your pull request

## Note
- Avoid using mutation as much as possible
- Use tail recursive functions instead of imperative loops
- Do not use JavaScript interoperability 
