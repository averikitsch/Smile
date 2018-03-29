close all
clear all
clc

% Load data sets

for i = 1:4
    happytxt = sprintf('setup1_%d_happy.mat', i);
    sadtxt = sprintf('setup1_%d_sad.mat', i);
    stressedtxt = sprintf('setup1_%d_stressed.mat', i);
    relaxtxt = sprintf('setup1_%d_relax.mat', i);
    happy(i) = load(happytxt);
    sad(i) = load(sadtxt);
    stressed(i) = load(stressedtxt);
    relax(i) = load(relaxtxt);
end

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

% time axis
samples = size(happy(1).recordData, 1);
t = 10 / samples : 10 / samples : 10;

% Plot data in terms of emotional state
figure()
for i = 1:4
    subplot(2,2,i), plot(t, happy(i).recordData(:, F3), t, happy(i).recordData(:, AF4))
end
title('Happy'), legend('F3', 'AF4')

figure()
for i = 1:4
    subplot(2,2,i), plot(t, sad(i).recordData(:, F3), t, sad(i).recordData(:, AF4))
end
title('Sad'), legend('F3', 'AF4')

figure()
for i = 1:4
    subplot(2,2,i), plot(t, relax(i).recordData(:, F3), t, relax(i).recordData(:, AF4))
end
title('Relax'), legend('F3', 'AF4')

figure()
for i = 1:4
    subplot(2,2,i), plot(t, stressed(i).recordData(:, F3), t, stressed(i).recordData(:, AF4))
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
happyRQ = cell(8, 1);
sadRQ = cell(8, 1);
relaxRQ = cell(8, 1);
stressedRQ = cell(8, 1);

figure()
for i = 1:4 
    chanF3  = happy(i).recordData(:, F3);
    chanAF4 = happy(i).recordData(:, AF4);
    fftF3   = fft(chanF3, next2) / len;
    fftAF4  = fft(chanAF4, next2) / len;
    magF3   = 2 * abs(fftF3(1 : next2 / 2 + 1));
    magAF4  = 2 * abs(fftAF4(1 : next2 / 2 + 1));
    deciF3  = 10 * log10(abs(magF3) / max(abs(magF3)));
    deciAF4 = 10 * log10(abs(magAF4) / max(abs(magAF4)));
    happyRQ{2*i-1} = magF3(a:ab) ./ magAF4(a:ab);
    happyRQ{2*i}   = magF3(ab:b) ./ magAF4(ab:b);
    subplot(2, 4, i), plot(f(a:ab), deciF3(a:ab) ./ deciAF4(a:ab), f(a:ab), happyRQ{2*i-1})
    subplot(2, 4, i + 4), plot(f(ab:b), deciF3(ab:b) ./ deciAF4(ab:b), f(ab:b), happyRQ{2*i})
end
title('Happy (F3 / AF3)'), legend('RQ Decibel', 'RQ Linear')

figure()
for i = 1:4 
    chanF3  = sad(i).recordData(:, F3);
    chanAF4 = sad(i).recordData(:, AF4);
    fftF3   = fft(chanF3, next2) / len;
    fftAF4  = fft(chanAF4, next2) / len;
    magF3   = 2 * abs(fftF3(1 : next2 / 2 + 1));
    magAF4  = 2 * abs(fftAF4(1 : next2 / 2 + 1));
    deciF3  = 10 * log10(abs(magF3) / max(abs(magF3)));
    deciAF4 = 10 * log10(abs(magAF4) / max(abs(magAF4)));
    sadRQ{2*i-1} = magF3(a:ab) ./ magAF4(a:ab);
    sadRQ{2*i}   = magF3(ab:b) ./ magAF4(ab:b);
    subplot(2, 4, i), plot(f(a:ab), deciF3(a:ab) ./ deciAF4(a:ab), f(a:ab), sadRQ{2*i-1})
    subplot(2, 4, i + 4), plot(f(ab:b), deciF3(ab:b) ./ deciAF4(ab:b), f(ab:b), sadRQ{2*i})
end
title('Sad (F3 / AF3)'), legend('RQ Decibel', 'RQ Linear')

figure()
for i = 1:4 
    chanF3  = relax(i).recordData(:, F3);
    chanAF4 = relax(i).recordData(:, AF4);
    fftF3   = fft(chanF3, next2) / len;
    fftAF4  = fft(chanAF4, next2) / len;
    magF3   = 2 * abs(fftF3(1 : next2 / 2 + 1));
    magAF4  = 2 * abs(fftAF4(1 : next2 / 2 + 1));
    deciF3  = 10 * log10(abs(magF3) / max(abs(magF3)));
    deciAF4 = 10 * log10(abs(magAF4) / max(abs(magAF4)));
    relaxRQ{2*i-1} = magF3(a:ab) ./ magAF4(a:ab);
    relaxRQ{2*i}   = magF3(ab:b) ./ magAF4(ab:b);
    subplot(2, 4, i), plot(f(a:ab), deciF3(a:ab) ./ deciAF4(a:ab), f(a:ab), relaxRQ{2*i-1})
    subplot(2, 4, i + 4), plot(f(ab:b), deciF3(ab:b) ./ deciAF4(ab:b), f(ab:b), relaxRQ{2*i})
end
title('Relax (F3 / AF3)'), legend('RQ Decibel', 'RQ Linear')

figure()
for i = 1:4 
    chanF3  = stressed(i).recordData(:, F3);
    chanAF4 = stressed(i).recordData(:, AF4);
    fftF3   = fft(chanF3, next2) / len;
    fftAF4  = fft(chanAF4, next2) / len;
    magF3   = 2 * abs(fftF3(1 : next2 / 2 + 1));
    magAF4  = 2 * abs(fftAF4(1 : next2 / 2 + 1));
    deciF3  = 10 * log10(abs(magF3) / max(abs(magF3)));
    deciAF4 = 10 * log10(abs(magAF4) / max(abs(magAF4)));
    stressedRQ{2*i-1} = magF3(a:ab) ./ magAF4(a:ab);
    stressedRQ{2*i}   = magF3(ab:b) ./ magAF4(ab:b);
    subplot(2, 4, i), plot(f(a:ab), deciF3(a:ab) ./ deciAF4(a:ab), f(a:ab), stressedRQ{2*i-1})
    subplot(2, 4, i + 4), plot(f(ab:b), deciF3(ab:b) ./ deciAF4(ab:b), f(ab:b), stressedRQ{2*i})
end
title('Stressed (F3 / AF3)'), legend('RQ Decibel', 'RQ Linear')

%%
% Find mean of frequencies for each emotion
aSad = [sadRQ{1}'; sadRQ{3}'; sadRQ{5}'; sadRQ{7}'];
bSad = [sadRQ{2}'; sadRQ{4}'; sadRQ{6}'; sadRQ{8}'];
aHappy = [happyRQ{1}'; happyRQ{3}'; happyRQ{5}'; happyRQ{7}'];
bHappy = [happyRQ{2}'; happyRQ{4}'; happyRQ{6}'; happyRQ{8}'];
aStressed = [stressedRQ{1}'; stressedRQ{3}'; stressedRQ{5}'; stressedRQ{7}'];
bStressed = [stressedRQ{2}'; stressedRQ{4}'; stressedRQ{6}'; stressedRQ{8}'];
aRelax = [relaxRQ{1}'; relaxRQ{3}'; relaxRQ{5}'; relaxRQ{7}'];
bRelax = [relaxRQ{2}'; relaxRQ{4}'; relaxRQ{6}'; relaxRQ{8}'];
alphaSad = mean(aSad)';
betaSad  = mean(bSad)';
alphaHappy = mean(aHappy)';
betaHappy  = mean(bHappy)';
alphaStressed = mean(aStressed)';
betaStressed  = mean(bStressed)';
alphaRelax = mean(aRelax)';
betaRelax  = mean(bRelax)';


% Do ttests to find where significant differences between frequency patterns
[~, alphaSHP] = ttest(aSad, aHappy);
[~, betaSHP]  = ttest(bSad, bHappy);
[~, alphaSRP] = ttest(aStressed, aRelax);
[~, betaSRP]  = ttest(bStressed, bRelax);


% Plot RQs for Sad / Happy and Stressed / Relaxes + significances. 
% The circles plotted are 1/(20*p), so any above 1 are significant at p < 0.05, above 5 are 
% significant at p < 0.01, and so on
alphaSH = alphaSad ./ alphaHappy;
betaSH  = betaSad ./ betaHappy;
alphaSR = alphaStressed ./ alphaRelax;
betaSR  = betaStressed ./ betaRelax;
sigline = ones(length(f(a:b)), 1);
figure(), plot(f(a:ab), alphaSH, f(ab:b), betaSH), hold on
plot(f(a:ab), 1 ./ alphaSHP / 20, 'ok', f(ab:b), 1 ./ betaSHP / 20, 'ok', f(a:b), sigline, 'r')
title('Sad / Happy RQ'), legend('Alpha', 'Beta'), hold off
figure(), plot(f(a:ab), alphaSR, f(ab:b), betaSR), hold on
plot(f(a:ab), 1 ./ alphaSRP / 20, 'ok', f(ab:b), 1 ./ betaSRP / 20, 'ok', f(a:b), sigline, 'r')
title('Stressed / Relax RQ'), legend('Alpha', 'Beta')


% Find and print frequencies at which there are significant differences
aIndexesSHP = find(alphaSHP < 0.05) + a;
bIndexesSHP = find(betaSHP < 0.05) + a;
aIndexesSRP = find(alphaSRP < 0.05) + a;
bIndexesSRP = find(betaSRP < 0.05) + a;
disp('Significant differences between happy and sad found at the following frequencies:')
for i = 1 : length(aIndexesSHP)
%     fprintf('   %.3f Hz\n', f(aIndexesSHP(i)))
    fprintf('%d, ', aIndexesSHP(i))
end
for i = 1 : length(bIndexesSHP)
%     fprintf('   %.3f Hz\n', f(bIndexesSHP(i)))
    fprintf('%d, ', bIndexesSHP(i))
end
disp(' ')
disp('Significant differences between relax and stressed found at the following frequencies:')
for i = 1 : length(aIndexesSRP)
%     fprintf('   %.3f Hz\n', f(aIndexesSRP(i)))
    fprintf('%d, ', aIndexesSRP(i))
end
for i = 1 : length(bIndexesSRP)
%     fprintf('   %.3f Hz\n', f(bIndexesSRP(i)))
    fprintf('%d, ', bIndexesSRP(i))
end
disp(' ')



% a = 65
% ab = 97
% b = 241
% l(arq) = 33
% l(brq) = 145