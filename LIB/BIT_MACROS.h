#define GET_BIT(Reg, PinNumber)               ( ((Reg)>>(PinNumber)) & 0x01 )
#define SET_BIT(Reg, PinNumber)                 Reg|=(1<<PinNumber)
#define CLR_BIT(Reg, PinNumber)					Reg&=~(1<<PinNumber)
#define TOGGLE_BIT(Reg, PinNumber)				Reg^=(1<<PinNumber)
#define ASSN_BIT(Reg, PinNumber,Value)          Reg=(Reg & ~(1<<PinNumber))|(Value<<PinNumber)


#define CONC_BITS(x,y)  x##y
#define GET_DEC(b3,b2,b1,b0)   ( (b3*8) + (b2*4) + (b1*2) + (b0*1) )
/*CHECK IF A SPECIFIC BIT IS SET ( = 1 ) IN ANY REGISTER AND RETURN TRUE IF BIT = 1 */
#define BIT_IS_SET(Reg,BIT_NUM)		(Reg & (1<<BIT_NUM))
/*SETTING THE WHOLE REGISTER (WHOLE REGISTER = 0XFF)*/
#define SET_ALL(Reg)				(Reg=0xFF)

/*CLEARING THE WHOLE REGISTER (WHOLE REGISTER = 0X00)*/
#define CLEAR_ALL(Reg)				(Reg=0x00)

#define BitManipulationGetBits(Reg, Bits_Offest, Bits_Width) \
((Reg) >> (Bits_Offest)) & (((1 << (Bits_Width)) - 1))

#define BitManipulationSetBits(Reg, Bits_Offest, Bits_Width, Value) \
(((Reg) & ~(((1<<(Bits_Width)) - 1) << (Bits_Offest))) | (((Value) & ((1<<(Bits_Width)) - 1)) << (Bits_Offest)))

#define INSERT_NUM(Reg, Num, Start_bit, Size)   Reg= Reg & ~((((1<<Size)-1)<<Start_bit)) | (Num<<Start_bit) & ~((((1<<Size)-1) <<Start_bit))
//0b00100101 & mask  ->  0b00000001 -> 0b00101001
//MASK 00111100, Start_bit = 2 , Size = 4
// 1111 == (10000 - 1)
#define GET_REG(Reg)							Reg
#define SET_REG(Reg)							Reg=0b11111111
#define CLR_REG(Reg)							Reg=0b00000000
#define TOGGLE_REG(Reg)							Reg^=(0b11111111)
#define ASSIGN_REG(Reg, Value)
