% Data Preparation
	num = [1:100];
	data = csvread('out.csv');

	for i = 1:100
		ave(i) = mean(data(i,:)); 
	end

% Fitting
	a = polyfit(num, ave, 2);
	a1 = polyval(a, num);
	figure;

% Parameter setting
	plot(x,ave,'.b');
	plot(x,a1,'r',x,ave,'.b');
	xlabel('Number of integers for Insertion Sort')%x???
	ylabel('Average Time among 1,000 tests (ms)')%y???
	set(gcf,'name','Experiments');
	title('Experimental Study for InsertionSort');
	grid off