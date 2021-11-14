# HMM
Hidden Markov Model applied to speech recognition.

This work is inspired by the KTH course "EQ2340: Pattern Recognition and Machine Learning".

# ToDo:
    - .wav file parser (kinda done in AudioFile.xpp)
    - Digital Signal Processing on audio files (spectrogram, amplitude correction on FFT, energy correction on FFT, windowing, ...).
    - Implementation of MFCC and Common Filter banks (e.g. FB40).
    - Implementation of common pdfs (Discrete distribution, Normal distribution, Multi-variable normal distribution, GMM, ...).
    - HMM and Markov Chain implementation.
    - Utility functions to split the wav files into datasets for training, validation and testing.


# Known issues:
    - libspeech/AudioFile.xpp, misplaced in the current folder structure. In the future, it might get moved to a separate library directory
    - libspeech/AudioFile.xpp, too naive. It just reads the wav file in binary mode 4 or 2 bytes at a time.
    - libspeech/AudioFile.xpp, sketchy casting from char to uintxx_t. In contrast with c++ core guideline.