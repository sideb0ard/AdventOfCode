#include <array>
#include <iostream>
#include <string>
#include <vector>

constexpr int kMarkerSize = 14;
std::vector<std::string> test_inputz = {
    "mjqjpqmgbljsphdztnvjfqwrcgsmlb",   "bvwbjplbgvbhsrlpgdmjqwftvncz",
    "nppdvjthqldpwncqszvftbrmjlhg",     "nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg",
    "zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw",
};

std::string real_input =
    "mzrzqrzqrrmcmgmrggvjvcczbczccdwdcwcpwwclwwbttdntnsnllpggqhgqgzqggvjjjfqfhh"
    "bbvzvmzvvfccnznwntnptpgpcplpwwvgvzvvcgvvbcvcqqhnqqbsbdsbbbgtgvtgvtgvvrfvvj"
    "bjcbcchnhrhvvrmmwzwzmwmggjwwwwzrrmbmbmbrrdjrjfrrrmrffzgghtggwddtllhchdhssh"
    "jjwfwsfssnbbnjncczsczzvpvssljsjgsjgjcgjggspsfsfhfppsqqzlzjllblsldsldlndnhn"
    "ffflwfwmwssvzzvqzzblzbbmrrfnrrqnnhfnnhphbhrrlvrlvrvcrrltrtmrrcscchdhqhfffr"
    "ddzsszwwrbrfftddbwwtdtnndrrghgcgfgrglllcdcsswvwsvszsddjwdwwcvwvmvhhlqlddbh"
    "brrnddpqpttrtctmcmjjtvjjfvvlcldltdtdqdllnrncrnrznzfnfsfnndqqbhhlnhhhsmhhfg"
    "hgppflllrhhvdddvrvnrnpplwplldttswsbwwtbbvwbwnnhcczmczmczclcttwcchllmsmbbrv"
    "bbsjsswbwwbtwtgtrgtrgrnggqwgwmwrmrqmmghhtbbrppjmpppjtjtffvqvbbwsspzsstlstl"
    "trrtmtrmrzmmgqqgmmpzmpzpmmgnnrjjgrjjhgjjsccjllwzzsddznnrsrttdllcnntvnttqjj"
    "qljqqwlqlmmfdfttzzvgvtvjjwvwsvvhbhrbhbwbzbppbplphpjpzppljjnttnvnggqbqffqgq"
    "rrjwjcjllcblbqqglqgqjqrrffjqqqcvqccgrgqgrqrnqqhphccvwwsgspprmprrwdrwrdwdrw"
    "rwswbsbcctscttwvvvstvthtrhhddtppgwwqpwwzpzgzszgzvggzqqmbqqrqsrqrmmjjfggztz"
    "dzvvqdqzddrrnmmtccsstdsdrrmrnnzzpggbmbqbcbzczppbjbssfzfcfvcvlclgcglcgllvcl"
    "cwwwpmwwjrrgtrtfrrnznssvvrjvrjrgjrrcsrrstrsrhrpplfljjwrwbbffdpfpzffrhhjrjd"
    "rrgpggbhhschcdcdcqcnncjcvjcvjvbvcbvbssnhhsddclcrcrjrdrtdtqdqrddddlcdcttzzl"
    "slblbqqcmmdgmmsnmnmccqmmljjncnhnchcdchddwsdssdrsscfcnffcqfqtfqqjcjrrvbrvvh"
    "svvlqlwwsccjbbgpgzgcgbgzgccpvcpvpddqrrqfqtqrqqcjjwvwttrwwblwlrwllnsshdhqdh"
    "qqjllzlflvlgllhnllstsbbdqqpnpwpmwwzhzvzcclcvcfvcvssdcdvdpphcphcppffndfnfmf"
    "bfwwgzwwwvhwwmcwwwtmtgtvggvbggzzthzzlbzbzmmhlllvgllmfmpmbbldbdnnzzjcctvvsd"
    "vssrpsslglqggcchvcvllzhhbcczjjgllvqlvlflglwwscctfcbmdjhgwtfhjrgvvvrmdcpsrt"
    "snvhwnnznnnmrhcnlnmjvdbqztspwbdwlttdtwlwdvqjpgqdzbnssglqczqwvfgdlbdmsbbmgg"
    "jdhddzvzlqhrggvvccmcmtqdmmpqvvstmqgvntdsmjbzbwstdrmjjmzfgmczjrftwrwnfbdmld"
    "dvzdfwwztldqfvdswfdwrfcgptmmjnzngwnflzlvtwpdsvllfwqjnjjjbfcwmgrvlhdvpgprnj"
    "thlqlbtlhflzwqjwtqtdzcvqbgtjlnmwchpjrgfndrnzwctjwvwsvflmgnqmplhhwljqcshqql"
    "dcnfrdbdcbslrtbnqrvhhjrddmjbtmcjzlqcdcqbfftsmpdpnfrjjwmdpmrvjjmppbnmcbvnzb"
    "phjcjlldnpdcwsqfgpmbszvjbpzngvncbfncpmghfrsssrnbbmhnjjvgmjzwtwlpszphgwvtjz"
    "dsmvvhnrplmnrllvqvphtbbrnlwmffdmmbhvzfcnbnlbspfwbcbjwgpnbsfpfbdqbnpfcqpngf"
    "qwlwcgrzlvfqgfsbppgmfzgjdntdvzvzclbrfwpqmvgmtmppsjzjhqbgjnntdnwvwljndqbtfg"
    "rjcfnlpsgsmbdljdzqfclgwhdgndzwbcthmrgzcjbhrrltlsznbsvswtsjbhwqzwchwzbtqmnr"
    "qfrzspwrqwwqwvczmntwggltjmvwdftplrgtrltmpvvgslvhctnwwcgtblmqtnsmqdgcbvzlcb"
    "rrsstzgzrgzgtmqtvsnzqqwlfgrjbdsvpdjpgmmczddbptwvpthvdjvrpqsbbgctrpqsdnczzb"
    "ttdrbflrllrnvjswslnghdqfqlnbcctwbnpvspfmrcnprpjzgwsdwlszzpdcgvzjsjtdgjnpwg"
    "tqmvsmsvzddcmfwtqjghrrrmvcjbccgrngcvvfvrrmmqmzsvhdqsfqpqnnhhpffrtblnzhwqms"
    "gvvzvgpbczsznzlnvsgjjzqbpjmvpjzqqpzpvplwsvgtwvrhlvggrpvztvchbcwflwhwmvdslv"
    "hsgpcqhdhcpvclgmzdngsmbplzrqgwflltzgsglflhqhpnnfszvtgprqhnjlrvwfsjfpcjzbzn"
    "sprtldvwjlnhqsdlfnwtlpzldfpnjpnnqfgqqrjrnszznlrjgwwlnbbznzcshtfqcprphgsldt"
    "gzzgqjvmjrtfhmgptrnqzmtfclqwgprvjptntgwhbqwhdjcfjtrmdwbslhqwgtcqwhjhhmltrl"
    "sqbvzqsjqsczvsqlsjdgmnjnpvmmwbsfnfnshmlrdgslbfrnhmdgcjgsqgwlbmlhhnfmcfnswm"
    "wgrzmpdmtrcmwgjlgrhzchmhmbjgjrfgdvplvngjnfdrscwqtnsspdszznnnjrdmvwbvnzmmdd"
    "bcvsphfqsbcmfmfgrcdfjptzqfsjsmjtbswtqzvtfpwbvqsgjzftfssdmcngtgbfmrrsjtllnp"
    "sztvgbpgpcrmqsgvcjrpprhqzjwlcdjpvgrqtjcglwnvzvqtncmndzbgpgfbprpqqjfbnzhfzl"
    "frgnfnbpjfrbtjgrgvmczthqsbfplnzvhqjmrrssnzjdhfvlngwptzzdshzhzfpzhmrcjmdvln"
    "lqtsnlbhqgplsltgznshthcwnpzpcgjjwhjstfcdtmmnvbgqzrjpsqwlmlbjnqtrfmbrdsbdlr"
    "rwqqvzdnmzhzvrhdftzldzjrtfgzlrwczbzzzqtthdcjtqpcfdwpqlzqmrnsnhwbzhjnqjzgfd"
    "cdcrqsjfhpjcdtwnvwzzbwfgdzcmmfvdvdpjsltcrbfqczvvbjscptjsvzndgwhzfjcqljndrc"
    "qzhssnqtmjmwjrsqdpqnhwsntqnmrwhvsnvrvpvwbndpmgsnchtnzpjgshcvjgwlwdhqbqhvcw"
    "qmwllhcgvbslqvwgswvnsqvvcphbglrvlsczcscznlwzrvjptmbmrgjlhvbrlghcwjdqjlgrcb"
    "rhfmbcwgclqzllqtmshbjnhwpgsgtljbwhgcsznvslmglcnmmgjlsptgdqlbtclfbfvjpmqgww"
    "bcvwtdhgjlpvgggjjvmltdgzjdsvtswgblgfcvdvtwrrfljtqjhdflhbtwmcdqpmdqrtjsvdhz"
    "stfnqjrzztnwslvwtvgvzfqlzfrhnthjfpvmwmdgrtzhbtwdfscdpwmwwrhgbmqrdftvjvrgzh"
    "bpqtqvvlwbmbvlszzqjwhtvwnsjcdcgdlwlrtvjsdqzngcdtpvsddsbqbhtrrpwqdhvdmnnncg"
    "ccszqtbcgwbdbwrnwrhpwprslbmhrmwpmqzvssfzvrmwrmrzmhrcwvbdtvdflgmrghqngwsgrn"
    "ctsnhpnmcmfmrtszttqtvvlhdjgplvgnjrtgnfgmdtvwzmzbtzvmhdvpcjqvgpsmdcfrbmqbrl"
    "snccldrfdldqfnsfzznqtvsgwbljgrvbdmggdmhvvdzjfllzwzpddcnvrfggsddqmczfnnfvrw"
    "smvfctctjqdrhvlntflccqgzg";

void AppendBuffer(std::vector<char>& buffer, char c) {
  if (buffer.size() < kMarkerSize) {
    buffer.push_back(c);
  } else {
    for (int i = 0; i < kMarkerSize - 1; i++) {
      buffer[i] = buffer[i + 1];
    }
    buffer[kMarkerSize - 1] = c;
  }
}

void PrintBuffer(std::vector<char>& buffer) {
  for (const auto& c : buffer) {
    std::cout << c;
  }
  std::cout << std::endl;
}

bool IsBufferStartOfPacket(std::vector<char>& buffer) {
  if (buffer.size() < kMarkerSize) return false;
  for (int i = 0; i < buffer.size() - 1; i++) {
    for (int j = i + 1; j < buffer.size(); j++) {
      if (buffer[i] == buffer[j]) return false;
    }
  }
  return true;
}

void FindMarker(const std::string& input) {
  std::cout << "FIND MARKER\n";
  std::vector<char> buffer;
  for (int i = 0; i < input.size(); i++) {
    AppendBuffer(buffer, input[i]);
    PrintBuffer(buffer);
    if (IsBufferStartOfPacket(buffer)) {
      std::cout << "PAcket found at idx:" << i + 1 << std::endl;
      break;
    }
  }
}

int main() {
  FindMarker(real_input);
  // for (const auto& i : test_inputz) {
  //   FindMarker(i);
  // }
}
