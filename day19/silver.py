import sys

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
                    func = None
                    # print(stat, comp, num)
                    if comp == '<':
                        func = lambda x, stat=stat, num=num: x[stat] < int(num)
                    elif comp == '>':
                        func = lambda x, stat=stat, num=num: x[stat] > int(num)
                    else:
                        assert False
                    parsed_rules.append((func, nxt))
                else:
                    parsed_rules.append((lambda _: True, rule))
            workflows[name] = parsed_rules
        else:
            item = {}
            line = line[1:-1].split(",")
            for att in line:
                att = att.split("=")
                item[att[0]] = int(att[1])
            items.append(item)
    # print(workflows, items)

    ans = 0
    for item in items:
        cur = "in"
        while cur not in ("A", "R"):
            for rule in workflows[cur]:
                # print(item, rule[0](item))
                if rule[0](item):
                    cur = rule[1]
                    break
            else:
                assert False
        if cur == "A":
            for v in item.values():
                ans += v
    print(ans)
