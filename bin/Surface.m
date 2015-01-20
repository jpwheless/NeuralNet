close all

x = [0:0.01:0.99]';
y = [0:0.01:0.99]';

for i=1:10
	fileName = ['output' int2str(i) '.txt'];
	Data = importdata(fileName);
	figure;
	surf(x, y, Data)
end
