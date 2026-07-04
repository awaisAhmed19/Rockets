#pragma once
#include <cmath>
#include <cstdio>
#include <functional>
#include <string>
#include <vector>

// Lightweight header-only test framework.
// Usage:
//   TEST_CASE("vector2 addition") {
//     Engine::math::vector2 a(1,2), b(3,4);
//     CHECK(a + b == Engine::math::vector2(4,6));
//     CHECK_NEAR((a + b).x, 4.f, 1e-5f);
//   }
//   int main() { return Tester::runAll(); }

namespace Tester {

struct TestCase {
  std::string name;
  std::function<void()> fn;
};

struct Failure {
  std::string testName;
  std::string expr;
  std::string file;
  int line;
};

inline std::vector<TestCase> &registry() {
  static std::vector<TestCase> cases;
  return cases;
}

inline std::vector<Failure> &failures() {
  static std::vector<Failure> f;
  return f;
}

inline std::string *currentTestName() {
  static std::string name;
  return &name;
}

inline void recordFailure(const char *expr, const char *file, int line) {
  failures().push_back({*currentTestName(), expr, file, line});
}

struct Registrar {
  Registrar(const std::string &name, std::function<void()> fn) {
    registry().push_back({name, std::move(fn)});
  }
};

inline int runAll() {
  int passedTests = 0;
  int totalTests = static_cast<int>(registry().size());

  for (auto &tc : registry()) {
    *currentTestName() = tc.name;
    size_t failuresBefore = failures().size();
    tc.fn();
    bool passed = (failures().size() == failuresBefore);
    if (passed) {
      ++passedTests;
      std::printf("[ PASS ] %s\n", tc.name.c_str());
    } else {
      std::printf("[ FAIL ] %s\n", tc.name.c_str());
      for (size_t i = failuresBefore; i < failures().size(); ++i) {
        const auto &f = failures()[i];
        std::printf("         %s:%d  CHECK(%s) failed\n", f.file.c_str(),
                    f.line, f.expr.c_str());
      }
    }
  }

  std::printf("\n%d/%d tests passed.\n", passedTests, totalTests);
  return (passedTests == totalTests) ? 0 : 1;
}

// float comparison helper
inline bool near(float a, float b, float eps = 1e-4f) {
  return std::abs(a - b) < eps;
}

} // namespace Tester

#define TEST_CASE_CONCAT_INNER(a, b) a##b
#define TEST_CASE_CONCAT(a, b) TEST_CASE_CONCAT_INNER(a, b)

#define TEST_CASE(name)                                                        \
  static void TEST_CASE_CONCAT(test_fn_, __LINE__)();                          \
  static Tester::Registrar TEST_CASE_CONCAT(test_reg_, __LINE__)(              \
      name, TEST_CASE_CONCAT(test_fn_, __LINE__));                             \
  static void TEST_CASE_CONCAT(test_fn_, __LINE__)()

#define CHECK(expr)                                                            \
  do {                                                                         \
    if (!(expr)) {                                                             \
      Tester::recordFailure(#expr, __FILE__, __LINE__);                        \
    }                                                                          \
  } while (0)

#define CHECK_NEAR(a, b, eps)                                                  \
  do {                                                                         \
    if (!Tester::near((a), (b), (eps))) {                                      \
      Tester::recordFailure(#a " ~= " #b, __FILE__, __LINE__);                 \
    }                                                                          \
  } while (0)

#define CHECK_THROWS(expr)                                                     \
  do {                                                                         \
    bool threw = false;                                                        \
    try {                                                                      \
      (expr);                                                                  \
    } catch (...) {                                                            \
      threw = true;                                                            \
    }                                                                          \
    if (!threw) {                                                              \
      Tester::recordFailure(#expr " to throw", __FILE__, __LINE__);            \
    }                                                                          \
  } while (0)
