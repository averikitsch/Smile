close all
clear all
clc

% Setup data collection
h = EmotivEEG('ED_F3');
h.Run

% Record and save data
happy=h.Record(10);
pause();
sad = h.Record(10);
pause();
stressed = h.Record(10);
pause();
relax = h.Record(10);

% load up saved data
h.LoadRecordedData(happy);
data1 = h.data;
h.LoadRecordedData(sad);
data2 = h.data;
h.LoadRecordedData(stressed);
data3=h.data;
h.LoadRecordedData(relax);
data4 = h.data;

% Plot data
figure();
subplot(2,2,1); plot(data1);
subplot(2,2,2); plot(data2);
subplot(2,2,3); plot(data3);
subplot(2,2,4); plot(data4);
legend(h.DataChannelsNames);