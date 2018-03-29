% Load data sets
happy(1) = load('setup2_1_happy.mat');
happy(2) = load('setup2_2_happy.mat');
happy(3) = load('setup2_3_happy.mat');
%happy(4) = load('setup2_4_happy.mat');
sad(1) = load('setup2_1_sad.mat');
sad(2) = load('setup2_2_sad.mat');
sad(3) = load('setup2_3_sad.mat');
%sad(4) = load('setup2_4_sad.mat');
relax(1) = load('setup2_1_relax.mat');
relax(2) = load('setup2_2_relax.mat');
relax(3) = load('setup2_3_relax.mat');
%relax(4) = load('setup2_4_relax.mat');
stressed(1) = load('setup2_1_stressed.mat');
stressed(2) = load('setup2_2_stressed.mat');
stressed(3) = load('setup2_3_stressed.mat');
%stressed(4) = load('setup2_4_stressed.mat');

% Data channels in order
DataChannelsNames = {
    'COUNTER'
    'INTERPOLATED'
    'RAW CQ'
    'AF3'
    'F7'
    'F3' % signal 1
    'FC5'
    'T7'
    'P7' % good for noise
    'O1'
    'O2'
    'P8'
    'T8'
    'FC6'
    'F4'
    'F8'
    'AF4' % signal 2
    'GYROX'
    'GYROY'
    'TIMESTAMP'
    'TIMESTAMP'
    'FUNC ID'
    'FUNC VALUE'
    'MARKER'
    'SYNC SIGNAL'};

% Channel indexes
F3  = 6;
AF4 = 17;
O1 = 10;
FC5 = 7;
% time axis
samples = size(happy(1).recordData, 1);
t = 10 / samples : 10 / samples : 10;

% Plot data in terms of emotional state
figure()
for i = 1:3
    subplot(2,2,i), plot(t, happy(i).recordData(:, F3),t,happy(i).recordData(:, FC5), t, happy(i).recordData(:, O1))
end
title('Happy'), legend('F3', 'AF4')

figure()
for i = 1:3
    subplot(2,2,i), plot(t, sad(i).recordData(:, F3),t,sad(i).recordData(:, FC5), t, sad(i).recordData(:, O1))
end
title('Sad'), legend('F3', 'AF4')

figure()
for i = 1:3
    subplot(2,2,i), plot(t, relax(i).recordData(:, F3),t,relax(i).recordData(:, FC5), t, relax(i).recordData(:, O1))
end
title('Relax'), legend('F3', 'AF4')

figure()
for i = 1:3
    subplot(2,2,i), plot(t, stressed(i).recordData(:, F3),t,stressed(i).recordData(:, FC5), t, stressed(i).recordData(:, O1))
end
title('Stressed'), legend('F3', 'AF4')

% Calculate FFT for each channel we are interested in
sampFreq = 128;
len   = size(happy(1).recordData, 1);     % Length of signal
next2 = 2^nextpow2(len);                % Next power of 2 from length of y
f  = sampFreq / 2 * linspace(0, 1, next2 / 2 + 1)';
a  = find(f == 8);
ab = find(f == 12);
b  = find(f == 30);
figure()
for i = 1:3
    chanF3  = happy(i).recordData(:, F3);
    chanAF4 = happy(i).recordData(:, AF4);
    fftF3   = fft(chanF3, next2) / len;
    fftAF4  = fft(chanAF4, next2) / len;
    magF3   = 2 * abs(fftF3(1 : next2 / 2 + 1));
    magAF4  = 2 * abs(fftAF4(1 : next2 / 2 + 1));
    deciF3  = 20 * log10(abs(magF3)/max(abs(magF3)));
    deciAF4 = 20 * log10(abs(magAF4)/max(abs(magAF4)));
    subplot(2, 4, i), plot(f(a:ab), deciF3(a:ab) / deciAF4(a:ab), f(a:ab), magF3(a:ab) / magAF4(a:ab))
    subplot(2, 4, i + 4), plot(f(ab:b), deciF3(ab:b) / deciAF4(ab:b), f(ab:b), magF3(ab:b) / magAF4(ab:b))
end
title('Happy (F3 / AF3)'), legend('RQ Decibel', 'RQ Linear')
