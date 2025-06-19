# AudioDSP
## Scope
With this framework I want to be able to test different Audio DSP algorithms in C++ and port them fast to an embedded platform. <br>
Therefore I am using C++.<br>
To achieve this, this Framework needs:
- Selection of audio sources like impulse, sin, mic-input, noise source (AWGN), audio codecs...
- Pipeline which makes it easy to modify processing steps aswell as in-/output modules
- Visualize the signal like spectrum, spectrograms, etc. in real-time
- easy to port on any Linux/UNIX platform

## Installation
### Dependencies on Fedora
On Fedora install Catch2 with ``sudo dnf install catch2-devel``
<br> **Note Fedora 42:** Don`t use the catch2-devel-xxx.x86_64 rpm's. They provide an older version.
### Dependencies on macOS
Install catch2 via homebrew.

### Build
CMake

## To-Do
- create fft dsp processor
- test PortAudio in-/output class
- complex support
- add more GUI elemts with to observe phase, bode plot, cutoff freqs etc