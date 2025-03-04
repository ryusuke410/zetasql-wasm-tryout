import getExtLib from "es-ext-lib";

(async () => {
  const extLib = await getExtLib();

  // 関数の使用
  const result = extLib.add(5, 3);
  console.log(`5 + 3 = ${result}`);

  // クラスの使用
  const counter = new extLib.Counter(10);
  console.log(`Initial count: ${counter.getCount()}`);
  counter.increment();
  console.log(`After increment: ${counter.getCount()}`);
})();
