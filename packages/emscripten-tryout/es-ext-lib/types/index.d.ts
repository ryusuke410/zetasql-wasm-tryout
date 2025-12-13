export interface CounterInstance {
  increment(): void;
  getCount(): number;
  delete(): void;
}

export interface ExtLibModule {
  add(left: number, right: number): number;
  Counter: {
    new (initialValue: number): CounterInstance;
  };
}

declare function createExtLibModule(): Promise<ExtLibModule>;

export default createExtLibModule;
