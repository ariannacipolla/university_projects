from timm import create_model
import torch.nn as nn

def get_vit_model(num_classes=100):
    model = create_model('vit_base_patch16_224', pretrained=True)
    model.head = nn.Linear(model.head.in_features, num_classes)
    return model
