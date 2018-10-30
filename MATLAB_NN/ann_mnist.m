% 6522056 zy22056 Xiangjun Peng
clear;

% Initialize some variables for further use
num = 5000;
Label = zeros(num, 10);

% Load labels into the program
load('label.mat');
for i = 1 : num
  Label(i, label(i)+1) = 1;  
end

% Load images into the program
imname = dir('data\*.png');
for i = 1 : num
  path = strcat('data\',imname(i).name);
  Image_toreshape = im2double(imread(path));
  Image_toPCA(i,:) = reshape(Image_toreshape,1,[]);
end

% PCA
[coeff, Image, latent] = pca(Image_toPCA);
latent_calculation = cumsum(latent) ./ sum(latent);
threshold = 0.9;
for i = 1 : num
    if (latent_calculation(i) >= threshold)
        break;
    end
end
Valid_Dimension = i;
Image = Image(:,1:Valid_Dimension);

% Separate the test set and train set
train_size = num * 0.8;
counter = 1;
state = randperm(num);
for i = 1 : train_size 
    train_feature(counter,:) = Image(state(i),:);
    train_label(counter,:) = Label(state(i),:);
    counter = counter + 1;
end
counter = 1;
for i = train_size + 1 : num
    test_feature(counter,:) = Image(state(i),:);
    test_label(counter,:) = Label(state(i),:);
    counter = counter +1;
end

% Transposition to suit the input formats
train_feature = train_feature';
train_label = train_label';
test_feature = test_feature';
test_label = test_label';

% Setting Neural Network and Train it
net = feedforwardnet();
net = train(net, train_feature, train_label);
view(net);
save('ann_model.mat');

% Test and plot the confusion matrix
test = net(test_feature);
plotconfusion(test_label, test);