%             % Rudimentary machine learning
%             if self.learn
%                 % Find extraneous frequencies (as indexes)
%                 alphaIndexes = [f(alphaRQ > mean(alphaRQ) * 3), f(alphaRQ < mean(alphaRQ) / 3)];
%                 betaIndexes  = [f(betaRQ > mean(betaRQ) * 3), f(betaRQ < mean(betaRQ) / 3)];
%                 
%                 % See which set contains more of the extraneous frequencies
%                 posCount = 0;
%                 negCount = 0;
%                 alphaIndexes;
%                 betaIndexes;
%                 if ~isempty(alphaIndexes) || ~isempty(betaIndexes) 
%                 for index = [alphaIndexes, betaIndexes]
%                     if self.posFreqs.contains(index)
%                         posCount = posCount + 1;
%                     end
%                     if self.negFreqs.contains(index)
%                         negCount = negCount + 1;
%                     end
%                 end
%                 end
%                 
%                 
%                 % Case where they are the same (both zero common example)
%                 if negCount == posCount
%                     % Get user input
%                     feels = lower(input('Was your emotion more positive or negative? (p/n): ','s'));
%                     while feels ~= 'p' && feels ~= 'n'
%                         disp('Please answer p or n.');
%                         feels = lower(input('Was your emotion more positive or negative? (p/n): ','s'));
%                     end
%                     
%                     % Assign extraneous frequencies to the appropriate list
%                     for index = [alphaIndexes, betaIndexes]
%                         if feels == 'p'
%                             self.posFreqs.add(index);
%                         else
%                             self.negFreqs.add(index);
%                         end
%                     end
%                 % Case where there is more positive than negaitve
%                 elseif posCount > negCount
%                     % Verify guessed feeling
%                     verifeels = lower(input('Were you feeling positive? (y/n): ','s'));
%                     while verifeels ~= 'y' && verifeels ~= 'n'
%                         disp('Please answer y or n.');
%                         verifeels = lower(input('Were you feeling positive? (y/n): ','s'));
%                     end
%                     
%                     % Remove frequencies if in wrong set, add to correct one.
%                     for index = [alphaIndexes, betaIndexes]
%                         if verifeels == 'y'
%                             self.posFreqs.add(index);
%                             self.negFreqs.remove(index);
%                         else
%                             self.posFreqs.remove(index);
%                             self.negFreqs.add(index);
%                         end
%                     end
%                  % Case where there is more negaitve than positive
%                 else
%                     % Verify guessed feeling
%                     verifeels = lower(input('Were you feeling negative? (y/n): ','s'));
%                     while verifeels ~= 'y' && verifeels ~= 'n'
%                         disp('Please answer y or n.');
%                         verifeels = lower(input('Were you feeling negative? (y/n): ','s'));
%                     end
%                     
%                     % Remove frequencies if in wrong set, add to correct one.
%                     for index = [alphaIndexes, betaIndexes]
%                         if verifeels == 'y'
%                             self.posFreqs.remove(index);
%                             self.negFreqs.add(index);
%                         else
%                             self.posFreqs.add(index);
%                             self.negFreqs.remove(index);
%                         end
%                     end
%                 end
%             end
%             
%             
%             result = 0; %counter used for # of significant frequencies
%             % Check for high frequencies
%             for index = self.emotionFreqs
%                 if index < ab
%                     if alphaRQ(index - a + 1) > 3 % say, 5 for a threshold for now
%                         fprintf('User is experiencing stress/sadness. \n(ALPHA)\nFreq: %.3f\n', f(index))
%                         result = result + 1;
%                     end
%                 else
%                     if betaRQ(index - ab + 1) > 3 % say, 5 for a threshold for now
%                         fprintf('User is experiencing stress/sadness. \n(BETA)\nFreq: %.3f\n', f(index))
%                         result = result + 1;
%                     end
%                 end
%             end