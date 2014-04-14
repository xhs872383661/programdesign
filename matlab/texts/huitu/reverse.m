function RE=reverse(A)
%This is a function to reverse the color of image A 
%input a RGB image and it will return a unit8 RGB

s=size(A);
RE=im2double(A);
for i=1:s(1)
    for j=1:s(2)
        for k=1:3
            RE(i,j,k)=1-RE(i,j,k);
        end
    end
end
RE=im2uint8(RE);

% 2012/4/22