s = 'abcdefghijklmnopqrstuvwxyz';

length_min = 5;
length_max = 25;
num_samples = 100;
words = cell(num_samples,4); %A,B,C
s_end = size(s,2);

for ii = 1:num_samples
    length = randi([length_min length_max],[2,1]);
    words{ii,1} = s(randi([1 s_end],[1,length(1)]));
    words{ii,2} = s(randi([1 s_end],[1,length(2)]));
    perm = [ones(1,length(1)) 2*ones(1,length(2))];
    ind = perm(randperm(size(perm,2)));
    
    words{ii,3} = zeros([1 size(perm,2)]);
    words{ii,4} = zeros([1 size(perm,2)]);
    words{ii,3}(ind==1) = words{ii,1}(1:length(1));
    words{ii,3}(ind==2) = words{ii,2}(1:length(2));
    words{ii,4} = words{ii,3};
    words{ii,4}(ind==1) = words{ii,4}(ind==1)-32;
    words{ii,4} = char(words{ii,4});
    words{ii,3} = char(words{ii,3});
end

fid1 = fopen('my_input','w');
fid2 = fopen('my_truth','w');

for ii = 1:num_samples
    fprintf(fid1,'%s\n',words{ii,1});
    fprintf(fid1,'%s\n',words{ii,2});
    fprintf(fid1,'%s\n',words{ii,3});
    fprintf(fid2,'%s\n',words{ii,4});
end

fclose(fid1);
fclose(fid2);

