#!/sbin/octave -qf

echo off all

function [d] = dist(p1, p2)
a = p1(1)-p2(1);
b = p1(2)-p2(2);
d = sqrt(a.^2+b.^2);
end

function [retp,reti] = minDist(p1, uv)
% Todo: complete this function. It should return the point with minimal
% distance with respect to p1.
retp = p1;
reti = -1;
lastmin = inf;
len = length(uv(:,1));
for i = 1:len
	d = dist(p1, uv(i,:));
	if d == 0
		continue
	end
	if d < lastmin
		lastmin = d;
		reti = i;
		retp = uv(i,:);
	end
end
end

uv = load('uv').uv; 


% Temp debug. This tries to set the origin to another location.
%uv(5,1) = uv(9,1);
%uv(5,2) = uv(9,2)+50;
%disp(uv);

u = [uv(:,1)];
v = [uv(:,2)];

% Display one element of the matrix.
%disp(uv(1,1));

[_,index] = min(u);
left = uv(index,:);
[_,index] = max(u);
right = uv(index,:);
[_,index] = min(v);
bottom = uv(index,:);
[_,index] = max(v);
top = uv(index,:);

x=[left(1),right(1),top(1),bottom(1)];
y=[left(2),right(2),top(2),bottom(2)];

% Get the point and index of the closest point to each of the edges.
[p1,i1] = minDist(top, uv);
[p2,i2] = minDist(bottom, uv);
[p3,i3] = minDist(left, uv);
[p4,i4] = minDist(right, uv);

dists = [dist(p1, top), dist(p2, bottom), dist(p3, left), dist(p4, right)];

[minp, mini] = min(dists);

p = p1;
i = i1;
if mini == 1
p = p1;
i = i1;
elseif mini == 2
p = p2;
i = i2;
elseif mini == 3
p = p3;
i = i3;
elseif mini == 4
p = p4;
i = i4;
end

plot(x, y, "*", 'markersize', 20, uv(i,1), uv(i,2), "x", 'markersize', 20 , u, v, "o", 'markersize', 10);

printf('The origin point is: p%d(%d, %d)\n', i, p(1), p(2));

pause();
%input("Press any key to continue.");

