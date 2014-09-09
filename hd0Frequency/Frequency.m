clear all;close all;clc

%{

Frequency.m


OUTPUTS:

    ReFreq.xml
        Takes "Time" by Pink Floyd, eff-eff-tees it, then
        writes the real part of the fft as a opencv_matrix

    ImFreq.xml
        As above with the imaginary part of the fft

    sMap.xml
        Defines a size map based on audio power 


    cMap.xml
        Defines a color map
        



NOTES:
    Make .gif via matlab at the bottom.

%}


%% Get Song


[Time Fs] = wavread('03 Time.wav');
%%

Time = mean(Time,2);
while length(Time) > 10000
   
    Time = Time(1:2:end);
    
end


%% Size Map

% Container for Sizemap
sMap = zeros(size(Time));

% Base it on the power of the audio at that time
Pwr = Time.^2;

% Map Power onto [0, 1] 
Pwr = Pwr./max(Pwr);

% Cut in half since we want symmetry 
Pwr = Pwr(1:2:end);

% Put in sMap
sMap(1:length(Time)/2) = Pwr;
sMap(length(Time)/2+1:end) = Pwr(length(Time)/2:-1:1);

% Make smallest sphere 0.1
sMap = sMap + 0.1*ones(size(sMap));

plot(sMap)

%% Write

matToXML(sMap,'sMap');


%% Colormaps

% Total frames used in Frequency gif
totalFrames = 9146;

% Container for colormap output "cMap.xml"
cMap = zeros(totalFrames,3);

% Choose colormap
newC1 = colormap(jet(269));
close all

newC = [];
while size(newC,1) < size(cMap,1)
    newC = [newC; newC1];
end

cMap(1:size(cMap,1)/2,:) = newC(1:size(cMap,1)/2,:);
cMap(size(cMap,1)/2+1:end,:) = newC(size(cMap,1)/2:-1:1,:);


%%%%%%%%% Mapping Color by Power %%%%%%%%%%
% % Map Power onto [0, 4572]
% Pwr = 4572.*Pwr;
% 
% % Map Power onto [1, 4573]
% Pwr = Pwr + ones(size(Pwr));
% 
% % Cut Pwr in half since we copy vals
% Pwr = Pwr(1:2:end);
% 
% % The indices of CMAP we want
% cIdx = round(Pwr);

% % Choose MATLAB COLORMAP 
% CMAP = colormap(jet(totalFrames/2));
% close all

% % Assign values copied backwards for last half
% lastIdx = length(cIdx);
% cMap = [CMAP(cIdx,:); CMAP(cIdx(lastIdx:-1:1),:)];

% imagesc(cMap)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% Write 
matToXML(cMap, 'cMap');


%%
FT = fft(Time);

X = real(FT);
Y = imag(FT);
C = colormap(jet(length(FT)));

%%

newC = colormap(autumn(300));
newC2 = colormap(autumn(200));
newC3 = colormap(autumn(100));
newC4 = colormap(autumn(50));
newC5 = colormap(autumn(10));

cL = length(C);

while size(newC,1) < cL/2
    
    newC = [newC; newC];
    
end

while size(newC2,1) < cL/2
    
    newC2 = [newC2; newC2];
    
end

while size(newC3,1) < cL/2
    
    newC3 = [newC3; newC3];
    
end

while size(newC4,1) < cL/2
    
    newC4 = [newC4; newC4];
    
end

while size(newC5,1) < cL/2
    
    newC5 = [newC5; newC5];
    
end

C(1:cL/2,:) = newC(1:cL/2,:);
C(cL:-1:cL/2+1,:) = newC(1:cL/2,:);

C2 = zeros(size(C));

C2(1:cL/2,:) = newC2(1:cL/2,:);
C2(cL:-1:cL/2+1,:) = newC2(1:cL/2,:);

C3 = zeros(size(C));

C3(1:cL/2,:) = newC3(1:cL/2,:);
C3(cL:-1:cL/2+1,:) = newC3(1:cL/2,:);


C4 = zeros(size(C));

C4(1:cL/2,:) = newC4(1:cL/2,:);
C4(cL:-1:cL/2+1,:) = newC4(1:cL/2,:);


C5 = zeros(size(C));

C5(1:cL/2,:) = newC5(1:cL/2,:);
C5(cL:-1:cL/2+1,:) = newC5(1:cL/2,:);



close all
% scatter(X,Y,25,C,'fill')
% axis([-25 25 -30 30])
% axis off
% zoom(2)
% set(gcf, 'Color', 'w', 'Position', [100 100 1200 300]);
% set(gcf, 'PaperUnits', 'inches', 'PaperPosition', [1 1 12 3], 'PaperPositionMode', 'auto');


%% Testing making a .gif



figure(1)
filename = 'Frequency.gif';
for n = 1:length(X)/2
    FrameCount = n
    
    subplot(5,1,1)
    scatter(X(n),Y(n),25,C(n,:),'fill')
    hold on
    scatter(X(end-(n-1)),Y(end-(n-1)),25,C(end-(n-1),:),'fill')
    axis([-30 30 -30 30])
    axis off
    subplot(5,1,2)
    scatter(X(n),Y(n),25,C2(n,:),'fill')
    hold on
    scatter(X(end-(n-1)),Y(end-(n-1)),25,C2(end-(n-1),:),'fill')
    axis([-30 30 -30 30])
    axis off
    subplot(5,1,3)
    scatter(X(n),Y(n),25,C3(n,:),'fill')
    hold on
    scatter(X(end-(n-1)),Y(end-(n-1)),25,C3(end-(n-1),:),'fill')
    axis([-30 30 -30 30])
    axis off
    subplot(5,1,4)
    scatter(X(n),Y(n),25,C4(n,:),'fill')
    hold on
    scatter(X(end-(n-1)),Y(end-(n-1)),25,C4(end-(n-1),:),'fill')
    axis([-30 30 -30 30])
    axis off
    subplot(5,1,5)
    scatter(X(n),Y(n),25,C5(n,:),'fill')
    hold on
    scatter(X(end-(n-1)),Y(end-(n-1)),25,C5(end-(n-1),:),'fill')
    axis([-30 30 -30 30])
    axis off
    
    
    set(gcf, 'Color', 'w', 'Position', [0 0 1100 1000]);
    set(gcf, 'PaperUnits', 'inches', 'PaperPosition', [0 0 11 10], 'PaperPositionMode', 'auto');   
    drawnow
    frame = getframe(1);
    im = frame2im(frame);
    [imind,cm] = rgb2ind(im,256);
%     if n == 1;
%         imwrite(imind,cm,filename,'gif', 'Loopcount',inf);
%     else
%         imwrite(imind,cm,filename,'gif','WriteMode','append');
%     end
end

%% Making a .gif

figure(1)
filename = 'Frequency.gif';
for n = 1:length(X)
    
    scatter(X,Y,25,C,'fill')
    axis([-30 30 -30 30])
    axis off
    set(gcf, 'Color', 'w', 'Position', [100 100 1200 300]);
    set(gcf, 'PaperUnits', 'inches', 'PaperPosition', [1 1 12 3], 'PaperPositionMode', 'auto');   
    drawnow
    frame = getframe(1);
    im = frame2im(frame);
    [imind,cm] = rgb2ind(im,256);
    if n == 1;
        imwrite(imind,cm,filename,'gif', 'Loopcount',inf);
    else
        imwrite(imind,cm,filename,'gif','WriteMode','append');
    end
end











