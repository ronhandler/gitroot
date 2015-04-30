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

% Read the wav files.
f1='IcyWind.wav';
[v1,Fs]=wavread(f1);

f2='IcyWindLPF8k.wav';
[v2,Fs]=wavread(f2);

f3='IcyWind_noise_00db.wav';
[v3,Fs]=wavread(f3);

f4='IcyWind_noise_05db.wav';
[v4,Fs]=wavread(f4);

f5='IcyWind_noise_15db.wav';
[v5,Fs]=wavread(f5);

% Compare levels using SNR.
%s = snr(v1, v2);

% Print the result.
printf ("SNR of %s and %s is: %f\n", f1, f2, snr(v1,v2));
printf ("SNR of %s and %s is: %f\n", f1, f3, snr(v1,v3));
printf ("SNR of %s and %s is: %f\n", f1, f4, snr(v1,v4));
printf ("SNR of %s and %s is: %f\n", f1, f5, snr(v1,v5));

