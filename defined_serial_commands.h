/*
 * serial_commands.h
 *
 * Created: 19.1.2014 15:48:55
 *  Author: Jarkko Hautakorpi, jarkko.hautakorpi@gmail.com
 *
 * INCLUDE THIS HEADER FILE IN BOTH, RASPISCOPE FIRMWARE AND RASPBERRY PI GUI SOFTWARE!
 *
 * Commands can be changed/added at any time, but then both RaspiScope firmware
 * and Raspberry Pi side software must be recompiled, so that both have same commands
 * assigned.
 * https://docs.google.com/spreadsheet/pub?key=0Au5qPw_asHasdDQtaFVwaEJsSGtEeGVPMTZ5RHRaT1E&output=html
 *
 */ 


#ifndef SERIAL_COMMANDS_H_
#define SERIAL_COMMANDS_H_

#define EOL		'LF'		// ASCII LF, hex A, dec 10 (NL line feed, new line)
#define ESCAPE	'EOT'		// ASCII EOT, hex 4, dec 4 (en of transmission)

#define	COMMAND_SET_REGISTER_VALUE8BIT	2
#define	COMMAND_SET_REGISTER_VALUE16BIT	3
#define	COMMAND_GET_REGISTER_VALUE_8BIT	4
#define	COMMAND_GET_REGISTER_VALUE_16BIT	5
#define	COMMAND_START_CAPTURE	6
#define	COMMAND_STOP_CAPTURE	7
#define	COMMAND_SET_CAPTURE_SPEED	8
#define	COMMAND_ENABLE_ADC_CHANNELS_BM	9
#define	COMMAND_ENABLE_ADC_CHANNEL	10
#define	COMMAND_DISABLE_ADC_CHANNELS_BM	11
#define	COMMAND_DISABLE_ADC_CHANNEL	12

/*
#define	COMMAND_	13
#define	COMMAND_	14
#define	COMMAND_	15
#define	COMMAND_	16
#define	COMMAND_	17
#define	COMMAND_	18
#define	COMMAND_	19
#define	COMMAND_	20
#define	COMMAND_	21
#define	COMMAND_	22
#define	COMMAND_	23
#define	COMMAND_	24
#define	COMMAND_	25
#define	COMMAND_	26
#define	COMMAND_	27
#define	COMMAND_	28
#define	COMMAND_	29
#define	COMMAND_	30
#define	COMMAND_	31
#define	COMMAND_	32
#define	COMMAND_	33
#define	COMMAND_	34
#define	COMMAND_	35
#define	COMMAND_	36
#define	COMMAND_	37
#define	COMMAND_	38
#define	COMMAND_	39
#define	COMMAND_	40
#define	COMMAND_	41
#define	COMMAND_	42
#define	COMMAND_	43
#define	COMMAND_	44
#define	COMMAND_	45
#define	COMMAND_	46
#define	COMMAND_	47
#define	COMMAND_	48
#define	COMMAND_	49
#define	COMMAND_	50
#define	COMMAND_	51
#define	COMMAND_	52
#define	COMMAND_	53
#define	COMMAND_	54
#define	COMMAND_	55
#define	COMMAND_	56
#define	COMMAND_	57
#define	COMMAND_	58
#define	COMMAND_	59
#define	COMMAND_	60
#define	COMMAND_	61
#define	COMMAND_	62
#define	COMMAND_	63
#define	COMMAND_	64
#define	COMMAND_	65
#define	COMMAND_	66
#define	COMMAND_	67
#define	COMMAND_	68
#define	COMMAND_	69
#define	COMMAND_	70
#define	COMMAND_	71
#define	COMMAND_	72
#define	COMMAND_	73
#define	COMMAND_	74
#define	COMMAND_	75
#define	COMMAND_	76
#define	COMMAND_	77
#define	COMMAND_	78
#define	COMMAND_	79
#define	COMMAND_	80
#define	COMMAND_	81
#define	COMMAND_	82
#define	COMMAND_	83
#define	COMMAND_	84
#define	COMMAND_	85
#define	COMMAND_	86
#define	COMMAND_	87
#define	COMMAND_	88
#define	COMMAND_	89
#define	COMMAND_	90
#define	COMMAND_	91
#define	COMMAND_	92
#define	COMMAND_	93
#define	COMMAND_	94
#define	COMMAND_	95
#define	COMMAND_	96
#define	COMMAND_	97
#define	COMMAND_	98
#define	COMMAND_	99
#define	COMMAND_	100
#define	COMMAND_	101
#define	COMMAND_	102
#define	COMMAND_	103
#define	COMMAND_	104
#define	COMMAND_	105
#define	COMMAND_	106
#define	COMMAND_	107
#define	COMMAND_	108
#define	COMMAND_	109
#define	COMMAND_	110
#define	COMMAND_	111
#define	COMMAND_	112
#define	COMMAND_	113
#define	COMMAND_	114
#define	COMMAND_	115
#define	COMMAND_	116
#define	COMMAND_	117
#define	COMMAND_	118
#define	COMMAND_	119
#define	COMMAND_	120
#define	COMMAND_	121
#define	COMMAND_	122
#define	COMMAND_	123
#define	COMMAND_	124
#define	COMMAND_	125
#define	COMMAND_	126
#define	COMMAND_	127
#define	COMMAND_	128
#define	COMMAND_	129
#define	COMMAND_	130
#define	COMMAND_	131
#define	COMMAND_	132
#define	COMMAND_	133
#define	COMMAND_	134
#define	COMMAND_	135
#define	COMMAND_	136
#define	COMMAND_	137
#define	COMMAND_	138
#define	COMMAND_	139
#define	COMMAND_	140
#define	COMMAND_	141
#define	COMMAND_	142
#define	COMMAND_	143
#define	COMMAND_	144
#define	COMMAND_	145
#define	COMMAND_	146
#define	COMMAND_	147
#define	COMMAND_	148
#define	COMMAND_	149
#define	COMMAND_	150
#define	COMMAND_	151
#define	COMMAND_	152
#define	COMMAND_	153
#define	COMMAND_	154
#define	COMMAND_	155
#define	COMMAND_	156
#define	COMMAND_	157
#define	COMMAND_	158
#define	COMMAND_	159
#define	COMMAND_	160
#define	COMMAND_	161
#define	COMMAND_	162
#define	COMMAND_	163
#define	COMMAND_	164
#define	COMMAND_	165
#define	COMMAND_	166
#define	COMMAND_	167
#define	COMMAND_	168
#define	COMMAND_	169
#define	COMMAND_	170
#define	COMMAND_	171
#define	COMMAND_	172
#define	COMMAND_	173
#define	COMMAND_	174
#define	COMMAND_	175
#define	COMMAND_	176
#define	COMMAND_	177
#define	COMMAND_	178
#define	COMMAND_	179
#define	COMMAND_	180
#define	COMMAND_	181
#define	COMMAND_	182
#define	COMMAND_	183
#define	COMMAND_	184
#define	COMMAND_	185
#define	COMMAND_	186
#define	COMMAND_	187
#define	COMMAND_	188
#define	COMMAND_	189
#define	COMMAND_	190
#define	COMMAND_	191
#define	COMMAND_	192
#define	COMMAND_	193
#define	COMMAND_	194
#define	COMMAND_	195
#define	COMMAND_	196
#define	COMMAND_	197
#define	COMMAND_	198
#define	COMMAND_	199
#define	COMMAND_	200
#define	COMMAND_	201
#define	COMMAND_	202
#define	COMMAND_	203
#define	COMMAND_	204
#define	COMMAND_	205
#define	COMMAND_	206
#define	COMMAND_	207
#define	COMMAND_	208
#define	COMMAND_	209
#define	COMMAND_	210
#define	COMMAND_	211
#define	COMMAND_	212
#define	COMMAND_	213
#define	COMMAND_	214
#define	COMMAND_	215
#define	COMMAND_	216
#define	COMMAND_	217
#define	COMMAND_	218
#define	COMMAND_	219
#define	COMMAND_	220
#define	COMMAND_	221
#define	COMMAND_	222
#define	COMMAND_	223
#define	COMMAND_	224
#define	COMMAND_	225
#define	COMMAND_	226
#define	COMMAND_	227
#define	COMMAND_	228
#define	COMMAND_	229
#define	COMMAND_	230
#define	COMMAND_	231
#define	COMMAND_	232
#define	COMMAND_	233
#define	COMMAND_	234
#define	COMMAND_	235
#define	COMMAND_	236
#define	COMMAND_	237
#define	COMMAND_	238
#define	COMMAND_	239
#define	COMMAND_	240
#define	COMMAND_	241
#define	COMMAND_	242
#define	COMMAND_	243
#define	COMMAND_	244
#define	COMMAND_	245
#define	COMMAND_	246
#define	COMMAND_	247
#define	COMMAND_	248
#define	COMMAND_	249
#define	COMMAND_	250
#define	COMMAND_	251
#define	COMMAND_	252
*/


#endif /* SERIAL_COMMANDS_H_ */