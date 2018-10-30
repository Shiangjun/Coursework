% This function calculates the distance between any two cartesian coordinates.
% Copyright 2009-2010 The MathWorks, Inc.

function dist = distance(x1, y1, x2, y2)

  %dist = sqrt((x1 - x2)^2 + (y1 - y2)^2); % h1
  dist = max(abs(x1-x2),abs(y1-y2)); %h2
  %dist = abs(x1-x2)+abs(y1-y2); %h3