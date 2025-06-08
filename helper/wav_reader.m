clear; close all; clc;

% Choose your file
filename = '../Catch_tests/Data/test_f32_chirp.wav'

% Read the WAV file
[y, Fs] = audioread(filename);

fprintf("Loaded in the wav file\n")
