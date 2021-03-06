#ifndef TEST_SERVER_SOCKET_TEST_HELPERS_H_
#define TEST_SERVER_SOCKET_TEST_HELPERS_H_
//#include "tests/test_lib/mocks_stubs/socket_test_helpers.h"

#include <string>
#include <vector>
#include <sys/types.h>
#include "source/data_types/byte_array.h"

//std::string vectorUint8_to_string(const std::vector<uint8_t> &input);
//std::vector<uint8_t> string_to_vectorUint8(const std::string &input);
std::string generateTestString(size_t size, size_t offset=0);
std::string applyMask(const std::string &in, uint32_t mask);
std::string createMaskFragmentHeader(int opcode, size_t _size, uint32_t mask);
std::string createMaskFragment(int opcode, const std::string &in, uint32_t mask);
std::string maskMessageForTesting(std::string in, uint32_t mask, bool binary, size_t fragmentSize);
std::string createCloseControlMessage();

ByteArray  createTestHandshakeHeader();
//std::vector< ByteArray > createTestHandshakeHeaderVector();

#endif /* TEST_SERVER_SOCKET_TEST_HELPERS_H_ */