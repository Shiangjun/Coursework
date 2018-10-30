%% Display the path_cost, number of nodes expanded and number of nodes discovered
figure(3);

Strain1_Mean=[28.0416    21   38];
Strain2_Mean=[116    90    396];
Strain3_Mean=[180    156   396];

bar([1 2 3],[Strain1_Mean' Strain2_Mean' Strain3_Mean'])
set(gca,'xticklabel',{'h1','h2', 'h3'});
legend('Path cost','Expanded Num','Discovered Num')
pause; close all;