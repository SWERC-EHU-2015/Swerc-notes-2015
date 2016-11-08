template<typename T, typename F>
class BrentCycleDetection {
    F f;
public:
    PII findCycle(T x0) {
        // 1st part: search successive powers of two
        int power = 1, lambda = 1; T tortoise = x0, hare = f(x0);
        while (tortoise != hare) {
            if (power == lambda) {
                tortoise = hare;
                power *= 2;
                lambda = 0;
            }
            hare = f(hare);
            lambda++;
        }
        // 2nd part: Find the position of the first repetition of length lambda
        int mu = 0;
        tortoise = hare = x0;
        for (int i = 0; i < lambda; i++) hare = f(hare);
        // 3rd part: the hare and tortoise move at same speed till they agree
        while (tortoise != hare) {
            tortoise = f(tortoise);
            hare = f(hare);
            mu++;
        }
        return PII(mu, lambda);
    }
};
