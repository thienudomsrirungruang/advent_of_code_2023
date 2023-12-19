import sys

def upd(d: dict, k, v):
    d = d.copy()
    d[k] = v
    return d

# returns {optional(ranges), optional(ranges)}
def split_range(r: dict[str, (int, int)], rule):
    (stat, comp, num) = rule
    rev = False
    if comp == '>':
        rev = True
        (stat, comp, num) = (stat, '<', num + 1)
    
    assert stat in r.keys()

    range = r[stat]
    out = (upd(r, stat, (range[0], num)), upd(r, stat, (num, range[1])))
    if range[0] >= num:
        out = (None, out[1])
    if num >= range[1]:
        out = (out[0], None)
    
    if rev:
        out = (out[1], out[0])
    return out

if __name__ == "__main__":
    workflows = {}
    items = []
    first = True
    for line in sys.stdin:
        line = line.strip()
        if line == "":
            first = False
            continue
        if first:
            line = line.split("{")
            name = line[0]
            rules = line[1][:-1].split(",")
            parsed_rules = []
            for rule in rules:
                if rule.count(":") == 1:
                    rule = rule.split(":")
                    cond = rule[0]
                    nxt = rule[1]
                    stat = cond[0]
                    comp = cond[1]
                    num = cond[2:]
                    func = (stat, comp, int(num))
                    parsed_rules.append((func, nxt))
                else:
                    parsed_rules.append((None, rule))
            workflows[name] = parsed_rules
        else:
            item = {}
            line = line[1:-1].split(",")
            for att in line:
                att = att.split("=")
                item[att[0]] = int(att[1])
            items.append(item)

    start_range = {a: (1, 4001) for a in "xmas"}

    def find_ans(range, flow):
        if flow == 'A':
            ans = 1
            for v in range.values():
                ans *= v[1] - v[0]
            return ans
        elif flow == 'R':
            return 0
        else:
            ans = 0
            for rule in workflows[flow]:
                if rule[0] is None:
                    ans += find_ans(range, rule[1])
                else:
                    (t, f) = split_range(range, rule[0])
                    if t is not None:
                        ans += find_ans(t, rule[1])
                    range = f
                    if range is None:
                        break
            return ans
    
    print(find_ans(start_range, "in"))
                

