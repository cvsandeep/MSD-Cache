

void parameters(int BusOp, unsigned int Address, unsigned int SnoopResult, char param)
{

	switch(param)
	{
		case GetSnoopResult:
		{	
			printf("SnoopResult: Address 0x%x\n",Address);
			break;
		}
		case BusOperation:
		{
			printf("BusOp: %d, Address:0x%x, Snoop Result:%d,\n", BusOp, Address,SnoopResult);
			break;
		}
		case PutSnoopResult:
		{
			printf("SnoopResult: Address 0x%x SnoopResult: %d\n", Address, SnoopResult);
			break;
		}
		case MessageToCache:
		{
			printf("L2: %d 0x%x\n", Message, Address);
			break;
		}
		case READ_DATA:
		{
			printf("operation READ_DATA\n");
			break;
		}
		case WRITE_DATA:
		{
			printf("operation WRITE_DATA\n");
			break;
		}
		case READ_INSTRUCTION:
		{
			printf("operation READ_INSTRUCTION\n");
			break;
		}
		case SNOOPED_INVALIDATE:
		{
			printf("operation READ_INSTRUCTION\n");
			break;
		}
		case SNOOPED_READ:
		{
			printf("operation SNOOPED_READ\n");
			break;
		}
		case SNOOPED_WRITE:
		{
			printf("operation SNOOPED_WRITE\n");
			break;
		}
		case SNOOPED_READ_X:
		{
			printf("operation SNOOPED_READ_X\n");
			break;
		}
		case CLEAR_AND_RESET:
		{
			printf("operation CLEAR_AND_RESET\n");
			break;
		}
		case PRINT_CACHE_LINE:
		{
			printf("operation PRINT_CACHE_LINE\n");
			break;
		}
		case PRINT_CACHE_LINE:
		{
			printf("operation PRINT_CACHE_LINE\n");
			break;
		}
		default:
				printf("Invalid Operation or Address...\n");
	}
}