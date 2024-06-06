
// 参考P139和P160

// (gdb) x/6gx 0×4006f8
// 0x4006f8:	0X00000000004005a1	0x00000000004005c3
// 0x400708:	0X00000000004005a1	0x00000000004005aa
// 0x400718:	0x00000000004005b2	0x00000000004005bf


// 首先看汇编代码：
// #long switch_prob(long x,long n)
// #x in %rdi，n in %rsi

// 0000000000400590	<switch_prob>:
// 	400590:	48 83 ee 3c				sub		$0x3c,%rsi 	                # %rsi -= 60,即n = n - 60，得到index
// 	400594:	48 83 fe 05				cmp		$0x5,%rsi	                #比较n（index）和5
// 	400598:	77 29 					ja 		4005c3 <switch_prob+0x33>   # n（index）> 5就跳转到default：4005c3，也即0x400590（<switch_prob>）+0x33得到的0x4005c3
// 	#n<=5由跳转表处理

// 	40059a:	ff 24 f5 f8 06 40 00	jmpq	*0x4006f8(,%rsi,8)          #间接跳转到0x4006f8 + 8 * n
// 	# 跳到跳转表对应的位置，从跳转表来看，n（index）和5的取值只能是0-5，因为只有6个八字节

// 	# 先分析哪些情况会跳到4005a1，查跳转表发现有两个4005a1，即下面两种情况
// 	# （1）index=0，0x4006f8加上偏移量0不变，所以取出前4四字节存的0X4005a1；
// 	# （2）index=2时，0x4006f8加上偏移量16（十进制）得到0x400708，所以取出前4四字节存的0X4005a1；
// 	4005a1:	48 8d 04 fd 00 00 00	lea 	0x0(,%rdi,8),%rax           #%rax=0x0 + 8*x
// 	4005a8:	00
// 	4005a9:	c3						retq

//  #哪些情况会跳到4005aa，查表只有一种，是0x400708后四字节存储的，所以
//  #index=3时，0x4006f8加上偏移量24得到0x400708+8，取出后4四字节存的0X4005aa
// 	4005aa:	48 89 f8 				mov		%rdi,%rax	                #%rax=x
// 	4005ad: 48 c1 f8 03 			sar 	$0x3,%rax	                #%rax=x>>3
// 	4005b1: c3						retq

// 	#查表得到0x400718:
// 	#index=4，0x4006f8加上偏移量32得到0x400718,取出前4四字节存的4005b2
// 	4005b2:	48 89 f8				mov		%rdi,%rax	                #%rax = x
// 	4005b5: 48 c1 e0 04				shl		$0x4,%rax	                #%rax = x<<4
// 	4005b9: 48 29 f8 				sub		%rdi,%rax	                #%rax -= x
// 	4005bc: 48 89 c7				mov		%rax,%rdi	                #x = x << 4 - x

// 	#注意前一行没有retq，所以这里跟index=4直接没有break，查表得到0x400718后四个字节
// 	#index=5
// 	4005bf: 48 Of af ff				imul	%rdi,%rdi	                #x = x * x

// 	#default（index>5，即n>60+5)，同时查表发现index=1时，也会到4005c3
// 	4005c3: 48 8d 47 4b				lea		0x4b(%rdi),%rax             #%rax = 0x4b + x = 75 + x
// 	4005c7: c3						retq

long switch_prob(long x, long n)
{
    long result = x;
    switch (n)
    {
    /*Fill in code here*/
    case 60:
    case 62:
        result = 8 * x;
        break;
    case 63:
        result = x >> 3;
        break;
    case 64:
        result = (x << 4) - x;
    case 65:
        x = x * x;
    default:
        result = x + 75;
    }
    return result;
}
