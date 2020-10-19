#include <bits/stdc++.h>
using namespace std;
using lli = long long int;
const int len_start = 350125310;
const int len_period = 182129209;

const vector<int> blocks_start = {0, 528439, 1044958, 1570960, 2096307, 2623786, 3146794, 3667813, 4194916, 4718790, 5248570, 5778807, 6302952, 6827323, 7344183, 7865867, 8388846, 8912985, 9441174, 9965808, 10489710, 11015519, 11540336, 12062673, 12588863, 13113898, 13637462, 14159416, 14688604, 15217232, 15743705, 16268288, 16791916, 17318237, 17843865, 18367895, 18892286, 19414523, 19934327, 20460270, 20986282, 21517078, 22048901, 22574305, 23100384, 23629461, 24150764, 24672594, 25198480, 25723452, 26253304, 26777351, 27302709, 27826755, 28351507, 28878670, 29399534, 29924975, 30450118, 30970432, 31496850, 32019176, 32544276, 33071712, 33597132, 34121424, 34647493, 35171087, 35693502, 36214619, 36740854, 37265823, 37791696, 38310364, 38837268, 39360628, 39886304, 40417825, 40937953, 41464547, 41989867, 42515275, 43040976, 43566716, 44093161, 44620297, 45144197, 45666410, 46190766, 46715915, 47235963, 47759633, 48280229, 48805146, 49333120, 49863363, 50389871, 50914204, 51437669, 51962446, 52492993, 53017438, 53542266, 54062568, 54581892, 55106072, 55631342, 56151788, 56680029, 57209121, 57732112, 58258130, 58781974, 59305422, 59829907, 60351900, 60876937, 61399981, 61924050, 62445202, 62968167, 63499412, 64021009, 64547535, 65074295, 65600192, 66127698, 66657176, 67183457, 67707843, 68230875, 68759279, 69283069, 69808467, 70330101, 70852401, 71376137, 71897772, 72424539, 72945917, 73477034, 74000976, 74524291, 75047082, 75575594, 76102304, 76627455, 77154512, 77679446, 78202636, 78731816, 79256492, 79780517, 80305283, 80828752, 81349661, 81870968, 82392263, 82912671, 83435986, 83960897, 84487880, 85011178, 85536820, 86061556, 86582045, 87102622, 87625595, 88147209, 88669578, 89190380, 89711237, 90237482, 90758932, 91285975, 91806590, 92333408, 92854533, 93377651, 93912423, 94441237, 94964062, 95488573, 96013918, 96546952, 97075723, 97599381, 98125588, 98651046, 99180306, 99703093, 100227946, 100746847, 101267679, 101791059, 102313049, 102838710, 103366630, 103890318, 104412921, 104938320, 105457239, 105983525, 106509447, 107032804, 107555662, 108090043, 108619782, 109139851, 109666474, 110180420, 110711587, 111232046, 111755371, 112279653, 112799162, 113324004, 113849749, 114373589, 114894107, 115415311, 115938666, 116463690, 116992753, 117525804, 118051807, 118577320, 119102701, 119632279, 120151480, 120676822, 121200401, 121732115, 122257076, 122787595, 123313425, 123834077, 124360809, 124881518, 125404722, 125927383, 126453151, 126976237, 127500870, 128023840, 128549018, 129074738, 129605402, 130128117, 130656106, 131173527, 131697449, 132226062, 132751646, 133274325, 133805972, 134329708, 134855303, 135379941, 135903880, 136420875, 136943639, 137468119, 137993885, 138523096, 139052124, 139571996, 140095516, 140625513, 141148976, 141674013, 142199318, 142716375, 143240347, 143770105, 144294571, 144817829, 145346059, 145867249, 146392919, 146915025, 147441342, 147968860, 148491147, 149018262, 149540604, 150064669, 150590873, 151117380, 151639061, 152155870, 152683045, 153208618, 153734710, 154260168, 154782277, 155305070, 155830540, 156352836, 156875666, 157395098, 157920821, 158442884, 158970412, 159493292, 160015772, 160536614, 161061619, 161589965, 162113061, 162634898, 163158611, 163685330, 164212762, 164736546, 165259634, 165781693, 166299698, 166827592, 167353001, 167876862, 168403441, 168921718, 169447706, 169970201, 170495645, 171019063, 171543904, 172066925, 172590397, 173106972, 173628178, 174149763, 174672817};
const vector<lli> values_start = {-1, 26622191657, 94608260214, 279413466667, 781765861648, 12192543157, 55384427610, 172792086345, 491939039296, 3025406444, 30465578342, 105055663372, 307812439266, 858962235776, 14634384927, 62022038328, 190834974428, 540984670943, 4576143552, 34680916686, 116514135462, 338959780989, 943629448655, 17313719204, 69305220698, 210632707014, 594800461396, 6279058060, 39309916194, 129097054815, 373163685661, 1036605256431, 20252978052, 77294950726, 232351034750, 653836969909, 8145511313, 44383459777, 142888369531, 410652347890, 454132771, 23476135004, 86056395491, 256167099226, 718575713753, 10194562769, 49953356247, 158028910304, 451808584940, 1756351452, 27015930770, 95678553642, 282322824535, 789674312158, 12443079432, 56065455469, 174643310844, 496971186648, 3185063747, 30899571483, 106235378497, 311019236004, 867679209385, 14910541891, 62772710496, 192875511589, 546531422810, 4752544839, 35160424830, 117817572956, 342502889641, 953260611955, 17617601445, 70131257736, 212878107324, 600904089822, 6472761414, 39836456280, 130528338414, 377054316145, 1047181081842, 20587876575, 78205298942, 234825616569, 660563576745, 8358657350, 44962850239, 144463315174, 414933491827, 589990750, 23845435085, 87060256769, 258895875817, 725993294058, 10429143285, 50591011851, 159762237335, 456520254323, 1905334753, 27420909130, 96779398170, 285315229044, 797808507363, 12701171020, 56767020640, 176550362024, 502155087198, 3348001133, 31342481179, 107439331338, 314291917775, 876575276344, 15190986134, 63535036727, 194947728552, 552164290409, 4929854445, 35642402260, 119127723066, 346064245216, 962941375246, 17923293948, 70962215938, 215136885002, 607044081403, 6665764718, 40361093317, 131954448794, 380930883954, 1057718681391, 20922129996, 79113893383, 237295430898, 667277225479, 8572141260, 45543159396, 146040758460, 419221425641, 725513528, 24213824277, 88061642049, 261617921990, 733392578723, 10662438385, 51225173449, 161486066338, 461206105447, 2053840466, 27824589477, 97876714812, 288298043200, 805916633091, 12956490164, 57461049880, 178436927846, 507283301741, 3511232347, 31786189283, 108645454359, 317570498285, 885487378042, 15473829270, 64303883756, 197037670189, 557845337803, 5110606275, 36133736304, 120463306681, 349694736193, 972810068443, 18234249292, 71807479728, 217434549150, 613289776340, 6863946456, 40899806861, 133418823503, 384911465422, 1068539018187, 21264216672, 80043781052, 239823126612, 674148210800, 8788847710, 46132228438, 147642013058, 423574084660, 863369657, 24588555695, 89080267201, 264386831028, 740919251073, 10900005599, 51870947770, 163241462444, 465977764208, 2204418942, 28233903963, 98989346410, 291322488072, 814137922424, 13216779379, 58168588705, 180360217011, 512511341425, 3676735982, 32236074725, 109868369185, 320894723917, 894523555993, 15758748796, 65078374859, 199142954247, 563568089986, 5291190109, 36624613846, 121797649574, 353321854422, 982669593569, 18548063599, 72660515006, 219753338233, 619592896244, 7063785085, 41443024205, 134895440809, 388925325503, 1079449815227, 21608785214, 80980414853, 242369160171, 681069044245, 9007923993, 46727739233, 149260778533, 427974343532, 1002672040, 24967218538, 90109578796, 267184788891, 748524885617, 11140468152, 52524592522, 165018252241, 470807577336, 2356790318, 28648091992, 100115225299, 294382942707, 822457096977, 13480726302, 58886070766, 182310534498, 517812851595, 3843686163, 32689892127, 111101972223, 324248003150, 903638709580, 16047033470, 65862013305, 201273103346, 569358433091, 5474491026, 37122877398, 123152069709, 357003548454, 992677470620, 18863680784, 73518451179, 222085449420, 625932228295, 7263648535, 41986309072, 136372241501, 392939684227, 1090361969024, 21952477815, 81914668112, 244908722598, 687972287873, 9225379982, 47318845563, 150867571305, 432342056918, 1140861545, 25342856630, 91130668695, 269960397340, 756069767059, 11380092155, 53175957802, 166788845794, 475620547338, 2509023497, 29061904467, 101240083742, 297440623521, 830768731254, 13743669598, 59600824360, 184253435231, 523094200665, 4011274011, 33145442757, 112340286516, 327614088568, 912788674001, 16338135828, 66653311346, 203424073494, 575205373409, 5659915357, 37626912580, 124522178627, 360727888698, 1002801272407, 19185081450, 74392108222, 224460294467, 632387723136, 7468031861, 42541880503, 137882440609, 397044829063, 23580833, 22305774094, 82875026244, 247519245449, 695068420733, 9450718657, 47931379479, 152532610694, 436868101172};

const vector<int> blocks_period = {0, 519374, 1037622, 1561463, 2085021, 2609809, 3134348, 3660595, 4184334, 4709396, 5228526, 5752378, 6277925, 6801249, 7320389, 7841566, 8367424, 8891893, 9413052, 9944570, 10469668, 10994650, 11520861, 12047162, 12566108, 13088066, 13615739, 14139884, 14665537, 15191169, 15718566, 16243276, 16770237, 17288967, 17812488, 18335382, 18859949, 19387594, 19910671, 20434170, 20960005, 21489330, 22006398, 22530851, 23054684, 23576013, 24102301, 24624460, 25146124, 25670729, 26197765, 26724655, 27248589, 27772911, 28287758, 28804909, 29330075, 29855529, 30379350, 30906734, 31434308, 31958419, 32484517, 33008612, 33533038, 34053112, 34575833, 35097774, 35622942, 36148702, 36672579, 37195153, 37719827, 38239924, 38761886, 39285374, 39806608, 40335070, 40863452, 41387678, 41911013, 42441261, 42968162, 43487959, 44010937, 44535462, 45054777, 45579870, 46106694, 46632625, 47154138, 47677897, 48203767, 48728499, 49257754, 49779293, 50303194, 50830208, 51356559, 51884864, 52406667, 52933350, 53456118, 53978307, 54491966, 55015299, 55541772, 56066670, 56596512, 57127346, 57652311, 58178538, 58706270, 59225450, 59753460, 60277972, 60803400, 61333209, 61856666, 62379298, 62901639, 63427882, 63955436, 64475965, 65002182, 65533070, 66058477, 66579189, 67101737, 67627205, 68149204, 68671646, 69193932, 69719027, 70240801, 70771897, 71296430, 71819822, 72344928, 72869348, 73385445, 73908760, 74431958, 74952943, 75479936, 76000689, 76523970, 77050638, 77577912, 78100969, 78626889, 79150429, 79669015, 80189507, 80717736, 81241243, 81765171, 82291741, 82816374, 83341173, 83866176, 84392514, 84914115, 85439568, 85962036, 86484825, 87007436, 87526594, 88048833, 88572366, 89093453, 89618095, 90141721, 90666443};
const vector<lli> values_period = {-1, 22243046259, 82704514474, 247055746505, 693808501400, 9409742799, 47819995527, 152229837633, 436045078887, 1257941924, 25661113806, 91995780815, 272312014589, 762462122641, 11582615422, 53726472815, 168285300023, 479688329462, 2638048583, 29412630867, 102193456843, 300032159198, 837813251927, 13965772600, 60204562696, 185894565604, 527555253827, 4151577565, 33526827143, 113376996320, 330432156766, 920448974600, 16578317196, 67306191652, 205198785533, 580029538687, 5811954979, 38040199083, 125645607422, 363781683518, 1011102343352, 19446481832, 75102667948, 226391795061, 637638084208, 7633446534, 42991524065, 139104697785, 400367266679, 128804455, 22591801428, 83652528743, 249632714944, 700813423808, 9632610838, 48425813524, 153876621039, 440521498068, 1398989430, 26044520617, 93037988212, 275145027182, 770163045864, 11825264494, 54386061209, 170078246331, 484562060528, 2792002308, 29831120260, 103331028105, 303124396889, 846218821926, 14232081984, 60928466229, 187862338453, 532904212180, 4320824123, 33986886879, 114627567615, 333831560380, 929689506429, 16872498358, 68105858553, 207372504456, 585938316349, 5998832221, 38548183713, 127026452302, 367535207053, 1021305472982, 19768760777, 75978712293, 228773128962, 644111217179, 7839057094, 43550430897, 140623963285, 404497056802, 259785646, 22947845234, 84620355833, 252263540659, 707964746286, 9858219392, 49039080657, 155543652898, 445052958547, 1542749214, 26435299864, 94100235728, 278032513282, 778012042712, 12074429522, 55063361534, 171919338503, 489566665331, 2950725161, 30262573682, 104503839712, 306312427782, 854884783865, 14505086541, 61670569336, 189879582740, 538387647978, 4494461532, 34458881984, 115910582696, 337319155212, 939169767726, 17172548368, 68921478787, 209589588902, 591964974291, 6189872339, 39067484303, 128438057086, 371372345176, 1031735890659, 20098500555, 76875037579, 231209592992, 650734210224, 8047762961, 44117752145, 142166101601, 408689021103, 392742403, 23309258867, 85602779604, 254934044315, 715223924482, 10087483108, 49662283684, 157237693511, 449657836259, 1688572269, 26831687839, 95177729450, 280961443754, 785973697993, 12326380643, 55748235202, 173781016998, 494627229972, 3110709245, 30697455107, 105685969513, 309525788473, 863619599463, 14782048707, 62423430159, 191926069824, 543950573982};

const int sum_start = 175147925;
const int sum_period = 91029304;
const int block_step = 1048576;

const lli M = 1ll << 40;

const lli s0 = 1611516670ll;

inline lli f(lli s){
	if(s == -1) return s0;
	return (s + (s >> 20) + 12345) & (M-1);
}

lli sum_block(const vector<int> & sums, const vector<lli> & values, lli n){
	int near = n / block_step;
	lli ans = sums[near];
	n = n % block_step;
	lli s = f(values[near]);
	for(int i = near+1; i <= near+n; ++i){
		ans += 1 - (s & 1);
		s = f(s);
	}
	return ans;
}

int main(){
	lli n;
	cin >> n;
	lli ans = 0;
	if(n <= len_start){
		ans = sum_block(blocks_start, values_start, n);
	}else{
		ans = sum_start;
		n -= len_start;
		lli full_periods = n / len_period;
		ans += sum_period * full_periods;
		n -= len_period * full_periods;
		ans += sum_block(blocks_period, values_period, n);
	}
	cout << ans << "\n";
	return 0;
}