
ross = ParallelTesting();
ross.run();
ross.delete();


%%

f = figure();
h = uicontrol('Position', [20 20 200 40], 'String', 'Continue', 'Callback', 'uiresume(gcbf)');
disp('immediate')
uiwait(gcf);
disp('after')
close(f);