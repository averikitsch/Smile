%% Example known to work
close all
clear all
clc

load fisheriris
t = ClassificationTree.fit(meas,species,'PredictorNames',{'SL' 'SW' 'PL' 'PW'})
view(t, 'mode', 'graph')


%% Testing with saved data

% Import data
[X, Y] = xlsread('classification.xlsx');
freqs = cell(1, 22);
for i = 8:29
    freqs{i - 7} = num2str(i);
end
ctree = ClassificationTree.fit(X, Y, 'PredictorNames', freqs);
view(ctree, 'mode', 'graph')