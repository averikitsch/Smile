%% Prediction Demo (Greg)
close all
clear all
clc

% Intro text
fprintf(['##########################################################################################\n\n'...
         'This script will demonstrate the ability of SMILE to predict Greg''s mood as being\n'...
         'positive, negative, or neutral.\n\n'...
         'We have prepared by running our program with machine learning turned on. Our program\n'...
         'allows users to save machine learning data and selectively reload it in any later\n'...
         'session.\n\nPress any button to continue...\n\n']);

pause()

% Run demo
h = EmotivSMILE();
h.runSMILE('demo');

% Give demo results
n = 0;
p = 0;
iter = h.demoResults.iterator();
while iter.hasNext()
    if strcmp(iter.next(), 'negative')
        n = n + 1;
    else
        p = p + 1;
    end
end
if n > p
    disp('User was feeling more negative')
elseif p > n
    disp('User was feeling more positive')
else
    disp('User was feeling neutral')
end
fprintf('Times counted negative: %d\nTimes counted positive: %d\n', n, p);

% View decision tree that we have previously demonstrated
h.veiwTree();


%% Learning Demo
close all

% Intro text
fprintf(['##########################################################################################\n\n'...
         'This script will demonstrate the machine learning of SMILE.\n\n'...
         'Press any button to continue...\n\n']);

pause()

h.delete();
h = EmotivSMILE();
h.runSMILE('learn');
h.delete();











