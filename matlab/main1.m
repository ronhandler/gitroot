#!/usr/bin/octave -qf

% SNR: SNR value of two signals.
% Usage: s = snr(s1, s2);
%
% SNR, or signal-to-noise ratio, is a measure used to compare the level of
% signal amplitude to the level of noise amplitude.
% It is defined to be the square of ratio between root mean squares of the
% signals:
%
%        /  RMS(A_signal) \
%  SNR = |  -------------  | ^ 2
%        \  RMS(A_noise)  /
%
function s=snr(in_vec, out_vec)
	signal = sqrt(mean(in_vec.^2));
	noise = sqrt(mean(out_vec.^2));
	s = (signal./noise).^2;
end

% Read the first wave file.
f1='IcyWind.wav';
[v1,Fs]=wavread(f1);

% Read the second wave file.
f2='IcyWindLPF8k.wav';
[v2,Fs]=wavread(f2);

% Compare levels using SNR.
s = snr(v1, v2);

% Print the result.
printf ("SNR of %s and %s is: %f\n", f1, f2, s);

