from google.colab import drive

import torch
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F
from torch.utils.data import DataLoader, Dataset
from torchvision import transforms, datasets
import torchvision.transforms as transforms

import os
import numpy as np
import matplotlib.pyplot as plt
import random

drive.mount("/content/drive")
data_dir = "/content/drive/MyDrive/archive1"

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
print(f"Используемое устройство: {device}")

transform = transforms.Compose([
    transforms.Resize((128, 128)),
    transforms.ToTensor(),
    transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225])
])

train_dataset = datasets.ImageFolder(
        root=os.path.join(data_dir, "train"),
        transform=transform
    )

test_dataset = datasets.ImageFolder(
        root=os.path.join(data_dir, "test"),
        transform=transform
    )

batch_size = 32
train_loader = DataLoader(train_dataset, batch_size=batch_size, shuffle=True)
test_loader = DataLoader(test_dataset, batch_size=batch_size, shuffle=False)

print(f"Классы: {train_dataset.classes}")
print(f"Размер тренировочной выборки: {len(train_dataset)}")
print(f"Размер тестовой выборки: {len(test_dataset)}")
print(f"Размер батча: {batch_size}")
print(f"Количество батчей в тренировочной выборке: {len(train_loader)}")
print(f"Количество батчей в тестовой выборке: {len(test_loader)}")

def visualize_images(dataset, num_images=10):
    indices = random.sample(range(len(dataset)), num_images)

    fig, axes = plt.subplots(2, 5, figsize=(15, 6))
    axes = axes.ravel()

    for i, idx in enumerate(indices):
        image, label = dataset[idx]

        # Денормализация
        image_np = image.numpy().transpose((1, 2, 0))
        mean = np.array([0.485, 0.456, 0.406])
        std = np.array([0.229, 0.224, 0.225])
        image_np = std * image_np + mean
        image_np = np.clip(image_np, 0, 1)

        axes[i].imshow(image_np)
        axes[i].set_title(f"Класс: {train_dataset.classes[label]}")
        axes[i].axis("off")

    plt.tight_layout()
    plt.show()

visualize_images(train_dataset, num_images=10)

class CNNModel(nn.Module):
    def __init__(self, num_classes=2):
        super(CNNModel, self).__init__()

        self.conv1 = nn.Conv2d(3, 32, kernel_size=3, padding=1)
        self.bn1 = nn.BatchNorm2d(32)

        self.conv2 = nn.Conv2d(32, 64, kernel_size=3, padding=1)
        self.bn2 = nn.BatchNorm2d(64)

        self.conv3 = nn.Conv2d(64, 128, kernel_size=3, padding=1)
        self.bn3 = nn.BatchNorm2d(128)

        self.conv4 = nn.Conv2d(128, 256, kernel_size=3, padding=1)
        self.bn4 = nn.BatchNorm2d(256)

        self.pool = nn.MaxPool2d(2, 2)

        self.dropout = nn.Dropout(0.5)

        self.fc1 = nn.Linear(256 * 8 * 8, 512)
        self.fc2 = nn.Linear(512, 128)
        self.fc3 = nn.Linear(128, num_classes)

    def forward(self, x):
        x = self.pool(F.relu(self.bn1(self.conv1(x))))
        x = self.pool(F.relu(self.bn2(self.conv2(x))))
        x = self.pool(F.relu(self.bn3(self.conv3(x))))
        x = self.pool(F.relu(self.bn4(self.conv4(x))))

        x = x.view(-1, 256 * 8 * 8)

        x = self.dropout(F.relu(self.fc1(x)))
        x = self.dropout(F.relu(self.fc2(x)))
        x = self.fc3(x)

        return x

model = CNNModel().to(device)
print("\nАрхитектура модели:")
print(model)

total_params = sum(p.numel() for p in model.parameters())
trainable_params = sum(p.numel() for p in model.parameters() if p.requires_grad)
print(f"\nВсего параметров: {total_params:,}")
print(f"Обучаемых параметров: {trainable_params:,}")

criterion = nn.CrossEntropyLoss()
optimizer = optim.Adam(model.parameters(), lr=0.001)

def calculate_accuracy(outputs, labels):
    _, predicted = torch.max(outputs.data, 1)
    correct = (predicted == labels).sum().item()
    total = labels.size(0)
    return correct / total

def train_model(model, train_loader, criterion, optimizer, num_epochs=25):
    model.train()
    train_losses = []
    train_accuracies = []

    for epoch in range(num_epochs):
        running_loss = 0.0
        running_accuracy = 0.0
        total_batches = len(train_loader)
        for batch_idx, (images, labels) in enumerate(train_loader):
            images, labels = images.to(device), labels.to(device)
            optimizer.zero_grad()

            outputs = model(images)
            loss = criterion(outputs, labels)

            loss.backward()
            optimizer.step()

            running_loss += loss.item()
            running_accuracy += calculate_accuracy(outputs, labels)

            if batch_idx % 5 == 0:
                print(f"Эпоха: {epoch + 1}/{num_epochs}, "
                      f"Батч: {batch_idx}/{total_batches}, "
                      f"Потеря: {loss.item():.4f}")

        epoch_loss = running_loss / total_batches
        epoch_accuracy = running_accuracy / total_batches

        train_losses.append(epoch_loss)
        train_accuracies.append(epoch_accuracy)

        print(f"Эпоха {epoch + 1}/{num_epochs} завершена -> "
              f"Средняя потеря: {epoch_loss:.4f}, "
              f"Средняя точность: {epoch_accuracy:.4f}"
        )
        print("-" * 50)

train_model(model, train_loader, criterion, optimizer)

def test_model(model, test_loader):
    model.eval()
    test_loss = 0.0
    correct = 0
    total = 0

    with torch.no_grad():
        for images, labels in test_loader:
            images, labels = images.to(device), labels.to(device)
            outputs = model(images)
            loss = criterion(outputs, labels)

            test_loss += loss.item()
            _, predicted = torch.max(outputs.data, 1)
            total += labels.size(0)
            correct += (predicted == labels).sum().item()

    accuracy = correct * 100 / total
    avg_loss = test_loss / len(test_loader)

    print("Оценка модели на тестовой выборке:")
    print(f"Средняя потеря: {avg_loss:.4f}")
    print(f"Точность: {accuracy:.2f}%")


test_model(model, test_loader)

def classify_test_images(model, test_loader, num_images=10):
    model.eval()

    indices = random.sample(range(len(test_dataset)), num_images)

    fig, axes = plt.subplots(2, 5, figsize=(15, 8))
    axes = axes.ravel()

    for i, idx in enumerate(indices):
        image, true_label = test_dataset[idx]

        image_batch = image.unsqueeze(0).to(device)

        with torch.no_grad():
            outputs = model(image_batch)
            probabilities = F.softmax(outputs, dim=1)
            _, predicted = torch.max(outputs, 1)

        image_np = image.numpy().transpose((1, 2, 0))
        mean = np.array([0.485, 0.456, 0.406])
        std = np.array([0.229, 0.224, 0.225])
        image_np = std * image_np + mean
        image_np = np.clip(image_np, 0, 1)

        predicted_class = test_dataset.classes[predicted.item()]
        true_class = test_dataset.classes[true_label]

        confidence = probabilities[0][predicted.item()].item() * 100

        axes[i].imshow(image_np)

        title_color = 'green' if predicted_class == true_class else 'red'

        axes[i].set_title(f"Ожидание: {true_class}\nПредсказание: {predicted_class}\nВероятность: {confidence:.1f}%",
                         color=title_color)
        axes[i].axis("off")

    plt.tight_layout()
    plt.show()

classify_test_images(model, test_loader, num_images=10)