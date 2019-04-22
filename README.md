# mapreduce

## Requirements

gcc(>=4.7)

## Building mapreduce

```
g++ mapreduce.cpp -o mapreduce -std=c++11 -Wall
```

## Usage

```
./mapreduce input_file output_directory
```

## Test

```
cd test
g++ generator.cpp -o generator -std=c++11 -Wall
./generator
cd ..
./mapreduce test/testdata.in test/output_data
```
You can find the result in test/output_data/result.txt
