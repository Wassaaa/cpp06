#include "Serializer.hpp"
#include <iostream>
#include <iomanip>

void printData(const Data* data, const std::string& prefix)
{
	std::cout << prefix << "Data object " << data << ":" << std::endl;
	std::cout << std::setw(4) << "" << "id: " << data->id << std::endl;
	std::cout << std::setw(4) << "" << "name: " << data->name << std::endl;
}

int main()
{
	std::cout << "\n=== Serializer Test ===\n" << std::endl;

	// Create and initialize original data
	std::cout << "1. Creating original Data object..." << std::endl;
	Data* original = new Data;
	original->id = 42;
	original->name = "John Doe";
	printData(original, "Original ");

	// Serialize the data
	std::cout << "\n2. Serializing Data to uintptr_t..." << std::endl;
	uintptr_t serialized = Serializer::serialize(original);
	std::cout << "   Serialized value: " << "0x" << std::hex << serialized << std::dec << std::endl;

	// Deserialize back to Data*
	std::cout << "\n3. Deserializing back to Data*..." << std::endl;
	Data* deserialized = Serializer::deserialize(serialized);
	printData(deserialized, "Deserialized ");

	// Verify the results
	std::cout << "\n4. Verification:" << std::endl;
	std::cout << "   Original address:    " << original << std::endl;
	std::cout << "   Deserialized address:" << deserialized << std::endl;
	std::cout << "   Addresses match:     " << (original == deserialized ? "YES" : "NO") << std::endl;
	std::cout << "   Data integrity:      " <<
		((original->id == deserialized->id &&
			original->name == deserialized->name) ? "INTACT" : "CORRUPTED") << std::endl;

	// Cleanup
	delete original;

	std::cout << "\n=== Test Complete ===\n" << std::endl;
	return 0;
}
