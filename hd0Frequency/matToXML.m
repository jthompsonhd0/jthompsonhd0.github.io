function [ out ] = matToXML( Mat, MatName)



outFile = fopen([MatName '.xml'], 'w');

n = size(Mat,1);
m = size(Mat,2);


L1 = '<?xml version="1.0"?>';
L2 = '<opencv_storage>';
L3 = ['<' MatName ' type_id="opencv-matrix">'];
L4 = ['  <rows>' num2str(n) '</rows>'];
L5 = ['  <cols>' num2str(m) '</cols>'];
L6 = '  <dt>f</dt>';
L7 = '  <data>';

%%

fprintf(outFile, '%s\n', L1);
fprintf(outFile, '%s\n', L2);
fprintf(outFile, '%s\n', L3);
fprintf(outFile, '%s\n', L4);
fprintf(outFile, '%s\n', L5);
fprintf(outFile, '%s\n', L6);
fprintf(outFile, '%s\n', L7);

%%

line = '   ';

%Go through matrix
for i = 1:n
    for j = 1:m 
   
        numS = num2str(Mat(i,j));
        if isempty(strfind(numS,'.'))
           %Then it doesn't end in a '.' and needs to 
           numS = [numS '.'];
        end
        
        line = [line ' ' numS];
        
        if j == m && i == n
           %Then the last line needs:
           line = [line '</data></' MatName '>'];
        end
    end
    
    fprintf(outFile, '%s\n', line);
    line = '   ';
end

%%

line = '</opencv_storage>';
fprintf(outFile, '%s\n', line);

fclose('all')

out = 'Writing successful';



end

