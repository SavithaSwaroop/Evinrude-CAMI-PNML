//Test code generated by MISTA

import junit.framework.*;

public class Switch_finalTester_RT extends TestCase{

	private Switch_final switch_final;
	
	protected void setUp()  throws Exception {
		switch_final = new Switch_final();
	}
	
	public void test1() throws Exception {
		System.out.println("Test case 1");
		switch_final.sys_0_17_2_66___builtin_puts(1);
		assertTrue("1_1", State_0_17_2_66___builtin_puts_post(1));
		switch_final.sys_0_17_3_84___builtin_puts(1);
		assertTrue("1_1_1", State_Global_EXIT(1));
	}

}