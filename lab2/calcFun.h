// std::vector<double> NAME(const std::vector<double> &values)
// {
//   std::vector<double> result(values.size());
// #pragma omp for schedule(SCHEDULE)
//   for (std::size_t i = 1; i < values.size() - 1; i++)
//   {
//     result[i] = (values[i - 1] + values[i] + values[i + 1]) / 3.0;
//   }
//   result.front() = result.front();
//   result.back() = result.back();
//   return result;
// }

std::vector<int> NAME(std::vector<int> &originalV)
{
  std::vector<int> resultV(originalV.size());
  omp_set_dynamic(0);
  omp_set_num_threads(8);
#pragma omp parallel for schedule(SCHEDULE)
  for (std::size_t i = 0; i < N; i++)
  {
    resultV[i] = (originalV[i - 1] + originalV[i] + originalV[i + 1]) / 3;
  }
  resultV.front() = originalV.front();
  resultV.back() = originalV.back();
  return resultV;
}

#undef NAME
#undef SCHEDULE