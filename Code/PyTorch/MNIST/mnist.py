import torch
from torch import nn
from torch.nn import functional as F
from torch import optim

import torchvision
from matplotlib import pyplot as plt

from utils import PlotCurve, PlotImage,OneHot


batch_size=512

#step1: load data
train_loader = torch.utils.data.DataLoader(
    torchvision.datasets.MNIST('mnist_data',train=True,download=True,
                                transform=torchvision.transforms.Compose([torchvision.transforms.ToTensor(),
                                                                        torchvision.transforms.Normalize((0.1307,),(0.3081,))])
                                ),
    batch_size=batch_size,shuffle=True)

test_loader = torch.utils.data.DataLoader(
    torchvision.datasets.MNIST('mnist_data',train=True,download=True,
                                transform=torchvision.transforms.Compose([torchvision.transforms.ToTensor(),
                                                                        torchvision.transforms.Normalize((0.1307,),(0.3081,))])
                                ),
    batch_size=batch_size,shuffle=False)

x,y = next(iter(train_loader))
print(x.shape,y.shape,x.min(),x.max(),)
# PlotImage(x,y,'image_sample')



#step2:net building
class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init__()

        #xw+b
        self.fc1=nn.Linear(28*28,256)
        self.fc2=nn.Linear(256,64)
        self.fc3=nn.Linear(64,10)
    
    def forward(self,x):
        #x: [b,1,28,28]
        x=F.relu(self.fc1(x))
        x=F.relu(self.fc2(x))
        x=self.fc3(x)
        return x

net = Net()
optimizer = optim.SGD(net.parameters(),lr=0.01,momentum=0.9)

train_loss=[]
#step3: training
for epoch in range(3):
    for batch_idx,(x,y) in enumerate(train_loader):
        #x;[b,1,28,28] y:[512]
        #[b,1,28,28]=>[b,784]   28*28=784
        x= x.view(x.size(0),28*28)
        #=>[b,10]
        out = net(x)
        y_onehot = OneHot(y)
        #[b,10]
        loss =F.mse_loss(out,y_onehot)

        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
        
        train_loss.append(loss.detach().numpy())

        if batch_idx%10 ==0:
            print(epoch,batch_idx,loss.item())
#we get optimal [w1,b1,w2,b2,w3,b3]
PlotCurve(train_loss)



#step4: testing
total_correct=0
for x,y in test_loader:
    x = x.view(x.size(0),28*28)
    out = net(x)
    #out: [b,10] => pred:[b]
    pred = out.argmax(dim=1)
    correct = pred.eq(y).sum().float().item()
    total_correct +=correct

total_num = len(test_loader.dataset)
acc= total_correct / total_num
print('test acc: ',acc)

x,y = next(iter(test_loader))
out= net(x.view(x.size(0),28*28))
pred = out.argmax(dim=1)
PlotImage(x,pred,'test')