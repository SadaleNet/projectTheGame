// Non-class, util library
/// class Utils - 
class Utils {
  // Operations
public:
  void Animate (T& target, const T start, const T end, std::function<double(double)> interpolater = linearInterpolater);
};

