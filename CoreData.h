#include"Constants.h"

struct Location {
	char loc_id [UUID_LENGTH];
	char desc[DESCRIPTION_LENGTH];
	char city[CITY_LENGTH];
	char country[COUNTRY_LENGTH];
	char region[REGION_LENGTH];
	char code[CODE_LENGTH];
	char zip[ZIP_LENGTH];
	double latitude;
	double longitude;
};

struct Customer {
	char cus_id[UUID_LENGTH];
	char loc_id[UUID_LENGTH];
	char desc[DESCRIPTION_LENGTH];
	char code[CODE_LENGTH];
};
