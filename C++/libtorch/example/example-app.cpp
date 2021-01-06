#include <torch/torch.h>

struct Net : torch::nn::Module {
  Net(int64_t N, int64_t M)
      : linear(register_module("linear", torch::nn::Linear(N, M))) {
    another_bias = register_parameter("b", torch::randn(M));
  }
  torch::Tensor forward(torch::Tensor input) {
    return linear(input) + another_bias;
  }
  torch::nn::Linear linear;
  torch::Tensor another_bias;
};

int main() {
  Net net(4, 5);
  // 输出网络的参数
  for (const auto& pair : net.named_parameters()) {//将各参数放到named_parameters()中
      std::cout << pair.key() << ": " << pair.value() << std::endl;
  }
  // 正向传播
  std::cout << "在正向模式中运行网络，并输出结果" << std::endl;
  std::cout << net.forward(torch::ones({2, 4})) << std::endl;
}
