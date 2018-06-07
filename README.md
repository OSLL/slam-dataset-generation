# slam-dataset-generation

## Roadmap

### CLI Application
The first goal is to build a CLI app that can generate a random world, generate critical points, generate a trajectory, simulate that trajectory, and save simulated sensor readings into a .bag file


### GUI Application
Once the CLI app is functional, we intend to wrap it in a Qt GUI.  Specifically, we'll add the functionality for a user to adjust/create the worlds, critical point selections, and trajectories.

## Dependencies
- **SVG++ 1.2.1**
    * Depends on **Boost >= 1.56**
    * Depends on **RapidXML NS 1.13**

## Building

First, check out the correct version of the included dependencies by issuing

```shell
git submodule init
git submodule update
```

Second, make sure Qt and Boost are installed on your machine.

Last, issue `make` in the root of the repo.
