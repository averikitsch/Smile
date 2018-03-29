% Initialize and start data collection
h = EmotivSMILE;
h.Run

% Report data every 0.5 seconds
% for i = 1:10
%     data_local = h.data;
%     data_local = data_local+1;
%     surf(data_local);
%     pause(0.5);
% end

% Save data to file, then recall the data and plot it
lastfilename = h.Record(30);
h.LoadRecordedData(lastfilename)
data_local = h.data;
surf(data_local);




%% Frequency analysis
close all
clc

% data = data_local;
% sampFreq = h.sampFreq;
data = rand(10000, 20); % generate random data in place of real data
sampFreq = 128;

len = size(data, 2);          % Length of signal
next2 = 2^nextpow2(len);      % Next power of 2 from length of y
f = sampFreq / 2 * linspace(0, 1, next2 / 2 + 1);

for channel = data
    FFT = fft(channel, next2) / len;
    mag = 2 * abs(FFT(1 : next2 / 2 + 1));
%     dB  = 20 * log10(abs(mag)/max(abs(mag)));
    plot(f, mag), title('Random Noise'), ylabel('Magnitude'), xlabel('Frequency (Hz)')
    pause()
end





