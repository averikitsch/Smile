% Note: labSendReceive

classdef ParallelTesting < handle
    
    % Fields
    properties (Access = public)
        cont;
    end
    
    % Public methods
    methods (Access = public)
        
        function self = ParallelTesting()
            disp('Initializing Object')
            self.cont = true;
        end
        
        function [] = run(self)
            disp('Running')
            funcs = {@getinput, @whileloop};
            matlabpool local 2
            try
                parfor i = 1:2
                    funcs{i}(self);
                end
            catch ME
                ME.cause
            end
            matlabpool close
        end
        
        function [] = getCont(self)
            fprintf('Cont = %d\n', self.cont);
        end
    end
    
    % Private methods
    methods (Access = public)
        
        % So it turns out that things running in different threads can't comminicate, ie changing
        % self.cont in one will not cause self.cont in the other to also change. This means we
        % cannot run simulataneous threads to collect stopping input for a while loop. 
        function [] = whileloop(self)
            disp('whileloop')
            i = 0;
            go = self.cont;
            while go && i < 10
                fprintf('Cont = %d\n', go);
                pause(1);
                i = i + 1;
                go = self.cont;
            end
            disp('endwhileloop')
        end
        
        function [] = getinput(self)
            disp('getinput')
            pause(5)
            self.cont = false;
            disp(self.cont);
            disp('endgetinput')
        end
    end
end
