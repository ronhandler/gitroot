#!/sbin/octave -qf

echo off all

function [d] = dist(p1, p2)
	a = p1(1)-p2(1);
	b = p1(2)-p2(2);
	d = sqrt(a.^2+b.^2);
end

function [retp,reti] = minDist(p1, uv)
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

% Return the minimal (orthogonal) distance between a point and a line.
function [d] = orthoDist(p, line1, line2)
	if p == line1 || p == line2
		d=0;
	else
		point = [p(1),p(2)];
		l1 = [line1(1),line1(2)];
		l2 = [line2(1),line2(2)];
		d = abs(det([l2-l1;point-l1]))/norm(l2-l1);
	end
end

% Return all the points on the line.
function [vec] = getPointsOnLine(uv, line1, line2)
	len = length(uv(:,1));
	threshold = 5;
	for i = 1:len
		if uv(i,:) == line1 || uv(i,:) == line2
			printf('continuing\n');
			continue
		end
		temp_dist = 1;
		temp_dist = orthoDist(uv(i,:), line1, line2);
		if temp_dist <= threshold
			vec(end+1,:) = [uv(i,1);uv(i,2)];
		end
	end
end

uv = load('uv').uv; 


% Temp debug. This tries to set the origin to another location.
%uv(5,1) = uv(9,1);
%uv(5,2) = uv(9,2)+50;
%disp(uv);

% Break uv into two u, v vectors.
u = [uv(:,1)];
v = [uv(:,2)];

% Get the edge points.
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

edges = [top; bottom; left; right];

p_origin = p1;
origin_ind = i1;
if mini == 1
p_origin = p1;
origin_ind = i1;
edges(1,:) = [];
elseif mini == 2
p_origin = p2;
origin_ind = i2;
edges(2,:) = [];
elseif mini == 3
p_origin = p3;
origin_ind = i3;
edges(3,:) = [];
elseif mini == 4
p_origin = p4;
origin_ind = i4;
edges(4,:) = [];
end

disp(edges);

printf('The origin point is: p%d(%d, %d)\n', origin_ind, p_origin(1), p_origin(2));

% Remove points that correspond to the edges.
points = uv;
len = length(points(:,1));
for i = len:-1:1
	tempp = points(i,:);
	if tempp==top || tempp==bottom || tempp==left || tempp==right || tempp==p_origin
		points(i,:) = [];
	end
end

% See how many points are between the origin and each of the edges.
len = length(points(:,1));
count = [0,0,0];
for i = 1:len
	threshold = 5;
	temp_dist = [0,0,0];
	temp_dist(1) = orthoDist(points(i,:), p_origin, edges(1,:));
	temp_dist(2) = orthoDist(points(i,:), p_origin, edges(2,:));
	temp_dist(3) = orthoDist(points(i,:), p_origin, edges(3,:));
	for j = 1:3
		if temp_dist(j) <= threshold
			% count(j) holds the number of points on the line between origin
			% and edge(i).
			count(j) = count(j) + 1;
		end
	end
end

% So if origin is point number 1, edge(i) for which count(i) is minimal is
% numbered 4, and between then there will be two points.
%printf('Counts: %d,%d,%d', count(1),count(2),count(3));

% Get the points p4, p9, p12.
[m,p4ind] = max(count);
p4 = edges(p4ind,:);
[m,p12ind] = min(count);
p12 = edges(p12ind,:);

	if p4ind<p12ind
	edges(p12ind,:) = [];
	count(p12ind) = [];
	edges(p4ind,:) = [];
	count(p4ind) = [];
else
	edges(p4ind,:) = [];
	count(p4ind) = [];
	edges(p12ind,:) = [];
	count(p12ind) = [];
end
[m,p9ind] = min(count);
p9 = edges(p9ind,:);

origin = uv(origin_ind,:);
p1 = origin

% Get the points p2, p3
row1 = getPointsOnLine(points, origin, p4);
[p2,p2ind] = minDist(origin,row1);
row1(p2ind,:) = [];
[p3,p3ind] = minDist(origin,row1);

% Get the points p10, p11
row4 = getPointsOnLine(points, p9, p12);
[p10,p10ind] = minDist(p9,row4);
row4(p10ind,:) = [];
[p11,p11ind] = minDist(p9,row4);

% Get point p5
col1 = getPointsOnLine(points, p1, p9);
[p5,p5ind] = minDist(p1,p9);

% Get point p8
col2 = getPointsOnLine(points, p4, p12);
[p8,p8ind] = minDist(p4,p12);

edges = [p4; p9; p12];
plot(uv(origin_ind,1), uv(origin_ind,2), "x", 'markersize', 20,
		edges(:,1), edges(:,2), "*", 'markersize', 20,
		u, v, "o", 'markersize', 10);
height = 10;
text(p_origin(1),p_origin(2)+10, "1");
text(p2(1),p2(2)+height, "2");
text(p3(1),p3(2)+height, "3");
text(p4(1),p4(2)+height, "4");
%text(p8(1),p8(2)+height, "8");
text(p9(1),p9(2)+height, "9");
text(p10(1),p10(2)+height, "10");
text(p11(1),p11(2)+height, "11");
text(p12(1),p12(2)+height, "12");

pause();
%input("Press any key to continue.");

