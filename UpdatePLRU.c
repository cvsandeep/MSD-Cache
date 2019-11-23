
// For 4-way set associative 
int UpdatePLRU(int set, int w)
{
	switch(w)
	{
		case 0:
		{
			PLRU[set][0] = 0;
			PLRU[set][1] = 0;
			break;
		}
		case 1:
		{
			PLRU[set][0] = 0;
			PLRU[set][1] = 1;
			break;
		}
		case 2:
		{
			PLRU[set][0] = 1;
			PLRU[set][2] = 0;
			break;
		}
		case 3:
		{
			PLRU[set][0] = 1;
			PLRU[set][2] = 1;
			break;
		}
		default:
		{
			printf("Invalid Input...\n");
			return -1;
		}
	}
	printf("PLRU Update Succesful...\n");
	return 0;
}