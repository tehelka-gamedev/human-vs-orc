# Human VS Orc

This project is a small simulation of a battle between two RPG units (a human and an orc).

## Goal of this project
The goal of this project is to have a **clean code architecture** and **be modular** to add easily new class, skills or attributes.

More info soon.

### How to add a new RPG Class

TODO

### How to create a new Skill

TODO

### How to add a new RPG attribute

TODO

## How to install

TODO

## Unit Testing

Unit testing is done with [Google Test](https://    github.com/google/googletest). The tests are located in the `TestProject` project.

### How to run the tests
Either run the project in Rider or Visual Studio, or execute ``.\HumanVSOrc\x64\Debug\TestProject.exe``

### Test coverage

I'm using [OpenCppCoverage](https://github.com/OpenCppCoverage/OpenCppCoverage) to generate the test coverage. To generate the report, run the following command:

```bash
OpenCppCoverage.exe --sources HumanVSOrc --excluded_sources gtest --excluded_sources Game -- .\HumanVSOrc\x64\Debug\TestProject.exe
```

It ignores the gtest and Game.cpp files as there is no point to test them.

As of the last commit, the test coverage is 87% although few parts are not tested because they just print debug messages.

_Screenshot of the report soon._
